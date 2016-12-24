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

#ifndef __lyGame__lyJson__
#define __lyGame__lyJson__

#ifdef __cplusplus
extern "C"
{
#endif

/* lyJson Types: */
#define lyJson_False 0
#define lyJson_True 1
#define lyJson_NULL 2
#define lyJson_Number 3
#define lyJson_String 4
#define lyJson_Array 5
#define lyJson_Object 6
	
#define lyJson_IsReference 256

/* The lyJson structure: */
typedef struct lyJson {
	struct lyJson *next,*prev;	/* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
	struct lyJson *child;		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

	int type;					/* The type of the item, as above. */

	char *valuestring;			/* The item's string, if type==lyJson_String */
	int valueint;				/* The item's number, if type==lyJson_Number */
	double valuedouble;			/* The item's number, if type==lyJson_Number */

	char *string;				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
} lyJson;

typedef struct lyJson_Hooks {
      void *(*malloc_fn)(size_t sz);
      void (*free_fn)(void *ptr);
} lyJson_Hooks;

/* Supply malloc, realloc and free functions to lyJson */
extern void lyJson_InitHooks(lyJson_Hooks* hooks);


/* Supply a block of JSON, and this returns a lyJson object you can interrogate. Call lyJson_Delete when finished. */
extern lyJson *lyJson_Parse(const char *value);
/* Render a lyJson entity to text for transfer/storage. Free the char* when finished. */
extern char  *lyJson_Print(lyJson *item);
/* Render a lyJson entity to text for transfer/storage without any formatting. Free the char* when finished. */
extern char  *lyJson_PrintUnformatted(lyJson *item);
/* Delete a lyJson entity and all subentities. */
extern void   lyJson_Delete(lyJson *c);

/* Returns the number of items in an array (or object). */
extern int	  lyJson_GetArraySize(lyJson *array);
/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
extern lyJson *lyJson_GetArrayItem(lyJson *array,int item);
/* Get item "string" from object. Case insensitive. */
extern lyJson *lyJson_GetObjectItem(lyJson *object,const char *string);

/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when lyJson_Parse() returns 0. 0 when lyJson_Parse() succeeds. */
extern const char *lyJson_GetErrorPtr();
	
/* These calls create a lyJson item of the appropriate type. */
extern lyJson *lyJson_CreateNull();
extern lyJson *lyJson_CreateTrue();
extern lyJson *lyJson_CreateFalse();
extern lyJson *lyJson_CreateBool(int b);
extern lyJson *lyJson_CreateNumber(double num);
extern lyJson *lyJson_CreateString(const char *string);
extern lyJson *lyJson_CreateArray();
extern lyJson *lyJson_CreateObject();

/* These utilities create an Array of count items. */
extern lyJson *lyJson_CreateIntArray(int *numbers,int count);
extern lyJson *lyJson_CreateFloatArray(float *numbers,int count);
extern lyJson *lyJson_CreateDoubleArray(double *numbers,int count);
extern lyJson *lyJson_CreateStringArray(const char **strings,int count);

/* Append item to the specified array/object. */
extern void lyJson_AddItemToArray(lyJson *array, lyJson *item);
extern void	lyJson_AddItemToObject(lyJson *object,const char *string,lyJson *item);
/* Append reference to item to the specified array/object. Use this when you want to add an existing lyJson to a new lyJson, but don't want to corrupt your existing lyJson. */
extern void lyJson_AddItemReferenceToArray(lyJson *array, lyJson *item);
extern void	lyJson_AddItemReferenceToObject(lyJson *object,const char *string,lyJson *item);

/* Remove/Detatch items from Arrays/Objects. */
extern lyJson *lyJson_DetachItemFromArray(lyJson *array,int which);
extern void   lyJson_DeleteItemFromArray(lyJson *array,int which);
extern lyJson *lyJson_DetachItemFromObject(lyJson *object,const char *string);
extern void   lyJson_DeleteItemFromObject(lyJson *object,const char *string);
	
/* Update array items. */
extern void lyJson_ReplaceItemInArray(lyJson *array,int which,lyJson *newitem);
extern void lyJson_ReplaceItemInObject(lyJson *object,const char *string,lyJson *newitem);

/* extern internal functions */
extern const char *lyJson_ParseString(lyJson *item,const char *str);
extern const char *lyJson_ParseValue(lyJson *item,const char *value);


#define lyJson_AddNullToObject(object,name)	lyJson_AddItemToObject(object, name, lyJson_CreateNull())
#define lyJson_AddTrueToObject(object,name)	lyJson_AddItemToObject(object, name, lyJson_CreateTrue())
#define lyJson_AddFalseToObject(object,name)		lyJson_AddItemToObject(object, name, lyJson_CreateFalse())
#define lyJson_AddNumberToObject(object,name,n)	lyJson_AddItemToObject(object, name, lyJson_CreateNumber(n))
#define lyJson_AddStringToObject(object,name,s)	lyJson_AddItemToObject(object, name, lyJson_CreateString(s))

#ifdef __cplusplus
}
#endif

#endif
