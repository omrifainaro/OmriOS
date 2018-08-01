#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct _LIST_ENTRY{
  struct _LIST_ENTRY* left;
  struct _LIST_ENTRY* right;
} LIST_ENTRY, *PLIST_ENTRY;

#define CONTAINING_RECORD(address, type, field) (\
    (type *)((char*)(address) -(unsigned long)(&((type *)0)->field)))

#endif
