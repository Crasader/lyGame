/*
  Copyright (c) 2009 Dave Gamble

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/* lyJson */
/* JSON parser in C. */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include "lyJson.h"

static const char *ep;

const char *lyJson_GetErrorPtr() {return ep;}

static int lyJson_strcasecmp(const char *s1,const char *s2)
{
	if (!s1) return (s1==s2)?0:1;if (!s2) return 1;
	for(; tolower(*s1) == tolower(*s2); ++s1, ++s2)	if(*s1 == 0)	return 0;
	return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

static void *(*lyJson_malloc)(size_t sz) = malloc;
static void (*lyJson_free)(void *ptr) = free;

static char* lyJson_strdup(const char* str)
{
      size_t len;
      char* copy;

      len = strlen(str) + 1;
      if (!(copy = (char*)lyJson_malloc(len))) return 0;
      memcpy(copy,str,len);
      return copy;
}

void lyJson_InitHooks(lyJson_Hooks* hooks)
{
    if (!hooks) { /* Reset hooks */
        lyJson_malloc = malloc;
        lyJson_free = free;
        return;
    }

	lyJson_malloc = (hooks->malloc_fn)?hooks->malloc_fn:malloc;
	lyJson_free	 = (hooks->free_fn)?hooks->free_fn:free;
}

/* Internal constructor. */
static lyJson *lyJson_New_Item()
{
	lyJson* node = (lyJson*)lyJson_malloc(sizeof(lyJson));
	if (node) memset(node,0,sizeof(lyJson));
	return node;
}

/* Delete a lyJson structure. */
void lyJson_Delete(lyJson *c)
{
	lyJson *next;
	while (c)
	{
		next=c->next;
		if (!(c->type&lyJson_IsReference) && c->child) lyJson_Delete(c->child);
		if (!(c->type&lyJson_IsReference) && c->valuestring) lyJson_free(c->valuestring);
		if (c->string) lyJson_free(c->string);
		lyJson_free(c);
		c=next;
	}
}

/* Parse the input text to generate a number, and populate the result into item. */
static const char *parse_number(lyJson *item,const char *num)
{
	double n=0,sign=1,scale=0;int subscale=0,signsubscale=1;

	/* Could use sscanf for this? */
	if (*num=='-') sign=-1,num++;	/* Has sign? */
	if (*num=='0') num++;			/* is zero */
	if (*num>='1' && *num<='9')	do	n=(n*10.0)+(*num++ -'0');	while (*num>='0' && *num<='9');	/* Number? */
	if (*num=='.' && num[1]>='0' && num[1]<='9') {num++;		do	n=(n*10.0)+(*num++ -'0'),scale--; while (*num>='0' && *num<='9');}	/* Fractional part? */
	if (*num=='e' || *num=='E')		/* Exponent? */
	{	num++;if (*num=='+') num++;	else if (*num=='-') signsubscale=-1,num++;		/* With sign? */
		while (*num>='0' && *num<='9') subscale=(subscale*10)+(*num++ - '0');	/* Number? */
	}

	n=sign*n*pow(10.0,(scale+subscale*signsubscale));	/* number = +/- number.fraction * 10^+/- exponent */
	
	item->valuedouble=n;
	item->valueint=(int)n;
	item->type=lyJson_Number;
	return num;
}

/* Render the number nicely from the given item into a string. */
static char *print_number(lyJson *item)
{
	char *str;
	double d=item->valuedouble;
	if (fabs(((double)item->valueint)-d)<=DBL_EPSILON && d<=INT_MAX && d>=INT_MIN)
	{
		str=(char*)lyJson_malloc(21);	/* 2^64+1 can be represented in 21 chars. */
		if (str) sprintf(str,"%d",item->valueint);
	}
	else
	{
		str=(char*)lyJson_malloc(64);	/* This is a nice tradeoff. */
		if (str)
		{
			if (fabs(floor(d)-d)<=DBL_EPSILON)			sprintf(str,"%.0f",d);
			else if (fabs(d)<1.0e-6 || fabs(d)>1.0e9)	sprintf(str,"%e",d);
			else										sprintf(str,"%f",d);
		}
	}
	return str;
}

/* Parse the input text into an unescaped cstring, and populate item. */
static const unsigned char firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
static const char *parse_string(lyJson *item,const char *str)
{
	const char *ptr=str+1;char *ptr2;char *out;int len=0;unsigned uc,uc2;
	if (*str!='\"') {ep=str;return 0;}	/* not a string! */
	
	while (*ptr!='\"' && *ptr && ++len) if (*ptr++ == '\\') ptr++;	/* Skip escaped quotes. */
	
	out=(char*)lyJson_malloc(len+1);	/* This is how long we need for the string, roughly. */
	if (!out) return 0;
	
	ptr=str+1;ptr2=out;
	while (*ptr!='\"' && *ptr)
	{
		if (*ptr!='\\') *ptr2++=*ptr++;
		else
		{
			ptr++;
			switch (*ptr)
			{
				case 'b': *ptr2++='\b';	break;
				case 'f': *ptr2++='\f';	break;
				case 'n': *ptr2++='\n';	break;
				case 'r': *ptr2++='\r';	break;
				case 't': *ptr2++='\t';	break;
				case 'u':	 /* transcode utf16 to utf8. */
					sscanf(ptr+1,"%4x",&uc);ptr+=4;	/* get the unicode char. */

					if ((uc>=0xDC00 && uc<=0xDFFF) || uc==0)	break;	// check for invalid.

					if (uc>=0xD800 && uc<=0xDBFF)	// UTF16 surrogate pairs.
					{
						if (ptr[1]!='\\' || ptr[2]!='u')	break;	// missing second-half of surrogate.
						sscanf(ptr+3,"%4x",&uc2);ptr+=6;
						if (uc2<0xDC00 || uc2>0xDFFF)		break;	// invalid second-half of surrogate.
						uc=0x10000 | ((uc&0x3FF)<<10) | (uc2&0x3FF);
					}

					len=4;if (uc<0x80) len=1;else if (uc<0x800) len=2;else if (uc<0x10000) len=3; ptr2+=len;
					
					switch (len) {
						case 4: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 3: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 2: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 1: *--ptr2 =(uc | firstByteMark[len]);
					}
					ptr2+=len;
					break;
				default:  *ptr2++=*ptr; break;
			}
			ptr++;
		}
	}
	*ptr2=0;
	if (*ptr=='\"') ptr++;
	item->valuestring=out;
	item->type=lyJson_String;
	return ptr;
}

/* Render the cstring provided to an escaped version that can be printed. */
static char *print_string_ptr(const char *str)
{
	const char *ptr;char *ptr2,*out;int len=0;unsigned char token;
	
	if (!str) return lyJson_strdup("");
	ptr=str;while ((token=*ptr) && ++len) {if (strchr("\"\\\b\f\n\r\t",token)) len++; else if (token<32) len+=5;ptr++;}
	
	out=(char*)lyJson_malloc(len+3);
	if (!out) return 0;

	ptr2=out;ptr=str;
	*ptr2++='\"';
	while (*ptr)
	{
		if ((unsigned char)*ptr>31 && *ptr!='\"' && *ptr!='\\') *ptr2++=*ptr++;
		else
		{
			*ptr2++='\\';
			switch (token=*ptr++)
			{
				case '\\':	*ptr2++='\\';	break;
				case '\"':	*ptr2++='\"';	break;
				case '\b':	*ptr2++='b';	break;
				case '\f':	*ptr2++='f';	break;
				case '\n':	*ptr2++='n';	break;
				case '\r':	*ptr2++='r';	break;
				case '\t':	*ptr2++='t';	break;
				default: sprintf(ptr2,"u%04x",token);ptr2+=5;	break;	/* escape and print */
			}
		}
	}
	*ptr2++='\"';*ptr2++=0;
	return out;
}
/* Invote print_string_ptr (which is useful) on an item. */
static char *print_string(lyJson *item)	{return print_string_ptr(item->valuestring);}

/* Predeclare these prototypes. */
static const char *parse_value(lyJson *item,const char *value);
static char *print_value(lyJson *item,int depth,int fmt);
static const char *parse_array(lyJson *item,const char *value);
static char *print_array(lyJson *item,int depth,int fmt);
static const char *parse_object(lyJson *item,const char *value);
static char *print_object(lyJson *item,int depth,int fmt);

/* Utility to jump whitespace and cr/lf */
static const char *skip(const char *in) {while (in && *in && (unsigned char)*in<=32) in++; return in;}

/* proxy to internal function */
const char *lyJson_ParseString(lyJson *item,const char *str) { return parse_string(item, str); }
const char *lyJson_ParseValue(lyJson *item,const char *value) { return parse_value(item, value); }

/* Parse an object - create a new root, and populate. */
lyJson *lyJson_Parse(const char *value)
{
	lyJson *c=lyJson_New_Item();
	ep=0;
	if (!c) return 0;       /* memory fail */

	if (!parse_value(c,skip(value))) {lyJson_Delete(c);return 0;}
	return c;
}

/* Render a lyJson item/entity/structure to text. */
char *lyJson_Print(lyJson *item)				{return print_value(item,0,1);}
char *lyJson_PrintUnformatted(lyJson *item)	{return print_value(item,0,0);}

/* Parser core - when encountering text, process appropriately. */
static const char *parse_value(lyJson *item,const char *value)
{
	if (!value)						return 0;	/* Fail on null. */
	if (!strncmp(value,"null",4))	{ item->type=lyJson_NULL;  return value+4; }
	if (!strncmp(value,"false",5))	{ item->type=lyJson_False; return value+5; }
	if (!strncmp(value,"true",4))	{ item->type=lyJson_True; item->valueint=1;	return value+4; }
	if (*value=='\"')				{ return parse_string(item,value); }
	if (*value=='-' || (*value>='0' && *value<='9'))	{ return parse_number(item,value); }
	if (*value=='[')				{ return parse_array(item,value); }
	if (*value=='{')				{ return parse_object(item,value); }

	ep=value;return 0;	/* failure. */
}

/* Render a value to text. */
static char *print_value(lyJson *item,int depth,int fmt)
{
	char *out=0;
	if (!item) return 0;
	switch ((item->type)&255)
	{
		case lyJson_NULL:	out=lyJson_strdup("null");	break;
		case lyJson_False:	out=lyJson_strdup("false");break;
		case lyJson_True:	out=lyJson_strdup("true"); break;
		case lyJson_Number:	out=print_number(item);break;
		case lyJson_String:	out=print_string(item);break;
		case lyJson_Array:	out=print_array(item,depth,fmt);break;
		case lyJson_Object:	out=print_object(item,depth,fmt);break;
	}
	return out;
}

/* Build an array from input text. */
static const char *parse_array(lyJson *item,const char *value)
{
	lyJson *child;
	if (*value!='[')	{ep=value;return 0;}	/* not an array! */

	item->type=lyJson_Array;
	value=skip(value+1);
	if (*value==']') return value+1;	/* empty array. */

	item->child=child=lyJson_New_Item();
	if (!item->child) return 0;		 /* memory fail */
	value=skip(parse_value(child,skip(value)));	/* skip any spacing, get the value. */
	if (!value) return 0;

	while (*value==',')
	{
		lyJson *new_item;
		if (!(new_item=lyJson_New_Item())) return 0; 	/* memory fail */
		child->next=new_item;new_item->prev=child;child=new_item;
		value=skip(parse_value(child,skip(value+1)));
		if (!value) return 0;	/* memory fail */
	}

	if (*value==']') return value+1;	/* end of array */
	ep=value;return 0;	/* malformed. */
}

/* Render an array to text */
static char *print_array(lyJson *item,int depth,int fmt)
{
	char **entries;
	char *out=0,*ptr,*ret;int len=5;
	lyJson *child=item->child;
	int numentries=0,i=0,fail=0;
	
	/* How many entries in the array? */
	while (child) numentries++,child=child->next;
	/* Allocate an array to hold the values for each */
	entries=(char**)lyJson_malloc(numentries*sizeof(char*));
	if (!entries) return 0;
	memset(entries,0,numentries*sizeof(char*));
	/* Retrieve all the results: */
	child=item->child;
	while (child && !fail)
	{
		ret=print_value(child,depth+1,fmt);
		entries[i++]=ret;
		if (ret) len+=strlen(ret)+2+(fmt?1:0); else fail=1;
		child=child->next;
	}
	
	/* If we didn't fail, try to malloc the output string */
	if (!fail) out=(char*)lyJson_malloc(len);
	/* If that fails, we fail. */
	if (!out) fail=1;

	/* Handle failure. */
	if (fail)
	{
		for (i=0;i<numentries;i++) if (entries[i]) lyJson_free(entries[i]);
		lyJson_free(entries);
		return 0;
	}
	
	/* Compose the output array. */
	*out='[';
	ptr=out+1;*ptr=0;
	for (i=0;i<numentries;i++)
	{
		strcpy(ptr,entries[i]);ptr+=strlen(entries[i]);
		if (i!=numentries-1) {*ptr++=',';if(fmt)*ptr++=' ';*ptr=0;}
		lyJson_free(entries[i]);
	}
	lyJson_free(entries);
	*ptr++=']';*ptr++=0;
	return out;	
}

/* Build an object from the text. */
static const char *parse_object(lyJson *item,const char *value)
{
	lyJson *child;
	if (*value!='{')	{ep=value;return 0;}	/* not an object! */
	
	item->type=lyJson_Object;
	value=skip(value+1);
	if (*value=='}') return value+1;	/* empty array. */
	
	item->child=child=lyJson_New_Item();
	if (!item->child) return 0;
	value=skip(parse_string(child,skip(value)));
	if (!value) return 0;
	child->string=child->valuestring;child->valuestring=0;
	if (*value!=':') {ep=value;return 0;}	/* fail! */
	value=skip(parse_value(child,skip(value+1)));	/* skip any spacing, get the value. */
	if (!value) return 0;
	
	while (*value==',')
	{
		lyJson *new_item;
		if (!(new_item=lyJson_New_Item()))	return 0; /* memory fail */
		child->next=new_item;new_item->prev=child;child=new_item;
		value=skip(parse_string(child,skip(value+1)));
		if (!value) return 0;
		child->string=child->valuestring;child->valuestring=0;
		if (*value!=':') {ep=value;return 0;}	/* fail! */
		value=skip(parse_value(child,skip(value+1)));	/* skip any spacing, get the value. */
		if (!value) return 0;
	}
	
	if (*value=='}') return value+1;	/* end of array */
	ep=value;return 0;	/* malformed. */
}

/* Render an object to text. */
static char *print_object(lyJson *item,int depth,int fmt)
{
	char **entries=0,**names=0;
	char *out=0,*ptr,*ret,*str;int len=7,i=0,j;
	lyJson *child=item->child;
	int numentries=0,fail=0;
	/* Count the number of entries. */
	while (child) numentries++,child=child->next;
	/* Allocate space for the names and the objects */
	entries=(char**)lyJson_malloc(numentries*sizeof(char*));
	if (!entries) return 0;
	names=(char**)lyJson_malloc(numentries*sizeof(char*));
	if (!names) {lyJson_free(entries);return 0;}
	memset(entries,0,sizeof(char*)*numentries);
	memset(names,0,sizeof(char*)*numentries);

	/* Collect all the results into our arrays: */
	child=item->child;depth++;if (fmt) len+=depth;
	while (child)
	{
		names[i]=str=print_string_ptr(child->string);
		entries[i++]=ret=print_value(child,depth,fmt);
		if (str && ret) len+=strlen(ret)+strlen(str)+2+(fmt?2+depth:0); else fail=1;
		child=child->next;
	}
	
	/* Try to allocate the output string */
	if (!fail) out=(char*)lyJson_malloc(len);
	if (!out) fail=1;

	/* Handle failure */
	if (fail)
	{
		for (i=0;i<numentries;i++) {if (names[i]) lyJson_free(names[i]);if (entries[i]) lyJson_free(entries[i]);}
		lyJson_free(names);lyJson_free(entries);
		return 0;
	}
	
	/* Compose the output: */
	*out='{';ptr=out+1;if (fmt)*ptr++='\n';*ptr=0;
	for (i=0;i<numentries;i++)
	{
		if (fmt) for (j=0;j<depth;j++) *ptr++='\t';
		strcpy(ptr,names[i]);ptr+=strlen(names[i]);
		*ptr++=':';if (fmt) *ptr++='\t';
		strcpy(ptr,entries[i]);ptr+=strlen(entries[i]);
		if (i!=numentries-1) *ptr++=',';
		if (fmt) *ptr++='\n';*ptr=0;
		lyJson_free(names[i]);lyJson_free(entries[i]);
	}
	
	lyJson_free(names);lyJson_free(entries);
	if (fmt) for (i=0;i<depth-1;i++) *ptr++='\t';
	*ptr++='}';*ptr++=0;
	return out;	
}

/* Get Array size/item / object item. */
int    lyJson_GetArraySize(lyJson *array)							{lyJson *c=array->child;int i=0;while(c)i++,c=c->next;return i;}
lyJson *lyJson_GetArrayItem(lyJson *array,int item)				{lyJson *c=array->child;  while (c && item>0) item--,c=c->next; return c;}
lyJson *lyJson_GetObjectItem(lyJson *object,const char *string)	{lyJson *c=object->child; while (c && lyJson_strcasecmp(c->string,string)) c=c->next; return c;}

/* Utility for array list handling. */
static void suffix_object(lyJson *prev,lyJson *item) {prev->next=item;item->prev=prev;}
/* Utility for handling references. */
static lyJson *create_reference(lyJson *item) {lyJson *ref=lyJson_New_Item();if (!ref) return 0;memcpy(ref,item,sizeof(lyJson));ref->string=0;ref->type|=lyJson_IsReference;ref->next=ref->prev=0;return ref;}

/* Add item to array/object. */
void   lyJson_AddItemToArray(lyJson *array, lyJson *item)						{lyJson *c=array->child;if (!item) return; if (!c) {array->child=item;} else {while (c && c->next) c=c->next; suffix_object(c,item);}}
void   lyJson_AddItemToObject(lyJson *object,const char *string,lyJson *item)	{if (!item) return; if (item->string) lyJson_free(item->string);item->string=lyJson_strdup(string);lyJson_AddItemToArray(object,item);}
void	lyJson_AddItemReferenceToArray(lyJson *array, lyJson *item)						{lyJson_AddItemToArray(array,create_reference(item));}
void	lyJson_AddItemReferenceToObject(lyJson *object,const char *string,lyJson *item)	{lyJson_AddItemToObject(object,string,create_reference(item));}

lyJson *lyJson_DetachItemFromArray(lyJson *array,int which)			{lyJson *c=array->child;while (c && which>0) c=c->next,which--;if (!c) return 0;
	if (c->prev) c->prev->next=c->next;if (c->next) c->next->prev=c->prev;if (c==array->child) array->child=c->next;c->prev=c->next=0;return c;}
void   lyJson_DeleteItemFromArray(lyJson *array,int which)			{lyJson_Delete(lyJson_DetachItemFromArray(array,which));}
lyJson *lyJson_DetachItemFromObject(lyJson *object,const char *string) {int i=0;lyJson *c=object->child;while (c && lyJson_strcasecmp(c->string,string)) i++,c=c->next;if (c) return lyJson_DetachItemFromArray(object,i);return 0;}
void   lyJson_DeleteItemFromObject(lyJson *object,const char *string) {lyJson_Delete(lyJson_DetachItemFromObject(object,string));}

/* Replace array/object items with new ones. */
void   lyJson_ReplaceItemInArray(lyJson *array,int which,lyJson *newitem)		{lyJson *c=array->child;while (c && which>0) c=c->next,which--;if (!c) return;
	newitem->next=c->next;newitem->prev=c->prev;if (newitem->next) newitem->next->prev=newitem;
	if (c==array->child) array->child=newitem; else newitem->prev->next=newitem;c->next=c->prev=0;lyJson_Delete(c);}
void   lyJson_ReplaceItemInObject(lyJson *object,const char *string,lyJson *newitem){int i=0;lyJson *c=object->child;while(c && lyJson_strcasecmp(c->string,string))i++,c=c->next;if(c){newitem->string=lyJson_strdup(string);lyJson_ReplaceItemInArray(object,i,newitem);}}

/* Create basic types: */
lyJson *lyJson_CreateNull()						{lyJson *item=lyJson_New_Item();if(item)item->type=lyJson_NULL;return item;}
lyJson *lyJson_CreateTrue()						{lyJson *item=lyJson_New_Item();if(item)item->type=lyJson_True;return item;}
lyJson *lyJson_CreateFalse()						{lyJson *item=lyJson_New_Item();if(item)item->type=lyJson_False;return item;}
lyJson *lyJson_CreateBool(int b)					{lyJson *item=lyJson_New_Item();if(item)item->type=b?lyJson_True:lyJson_False;return item;}
lyJson *lyJson_CreateNumber(double num)			{lyJson *item=lyJson_New_Item();if(item){item->type=lyJson_Number;item->valuedouble=num;item->valueint=(int)num;}return item;}
lyJson *lyJson_CreateString(const char *string)	{lyJson *item=lyJson_New_Item();if(item){item->type=lyJson_String;item->valuestring=lyJson_strdup(string);}return item;}
lyJson *lyJson_CreateArray()						{lyJson *item=lyJson_New_Item();if(item)item->type=lyJson_Array;return item;}
lyJson *lyJson_CreateObject()						{lyJson *item=lyJson_New_Item();if(item)item->type=lyJson_Object;return item;}

/* Create Arrays: */
lyJson *lyJson_CreateIntArray(int *numbers,int count)				{int i;lyJson *n=0,*p=0,*a=lyJson_CreateArray();for(i=0;a && i<count;i++){n=lyJson_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
lyJson *lyJson_CreateFloatArray(float *numbers,int count)			{int i;lyJson *n=0,*p=0,*a=lyJson_CreateArray();for(i=0;a && i<count;i++){n=lyJson_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
lyJson *lyJson_CreateDoubleArray(double *numbers,int count)		{int i;lyJson *n=0,*p=0,*a=lyJson_CreateArray();for(i=0;a && i<count;i++){n=lyJson_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
lyJson *lyJson_CreateStringArray(const char **strings,int count)	{int i;lyJson *n=0,*p=0,*a=lyJson_CreateArray();for(i=0;a && i<count;i++){n=lyJson_CreateString(strings[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
