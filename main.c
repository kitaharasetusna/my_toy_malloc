#include<assert.h>
#include<stdbool.h>
#include<stdio.h>

//how many bites
#define HEAP_CAP 640000
//how many chunks
#define CHUNK_LIST_CUP 1024

#define UNIMPLEMENTED()\
do{\
    fprintf(stderr, "%s:%d: TODO: %s is not implemented yet\n", \
                        __FILE__, __LINE__, __func__);\
}while(0)



//def of heap chunk
typedef struct 
{
    void* start;
    size_t size;
}Chunk;

//def of chunk list
//(a). alloced chunk list
//(b). freeed chunk list
typedef struct 
{
    //when del heap, we will set this to be 0
    size_t size;
    Chunk chunks[CHUNK_LIST_CUP];
}Chunk_List;




//0. our heap
char heap[HEAP_CAP] = {0};
size_t heap_size;
//------ V0: ----------
//when del heap, we will set this to be 0
//Heap_Chunk heap_alloced[HEAP_ALLOCED_CAP]={0};
//size_t heap_alloced_size;
//------ V0: ----------
Chunk_List alloced_chunks;


//------ V0: ----------
// Heap_Chunk heap_freed[HEAP_FREEDED_CAP]={0};
// size_t heap_freed_size;
//------ V0: ----------
Chunk_List freeded_chunks;


void chunk_list_dump(const Chunk_List* list)
{
    printf("Allocated Chunks (%zu):\n", list->size);
    for(size_t i=0; i<list->size; i++)
    {
        printf("    start: %p, size: %zu\n", list->chunks[i].start,
        list->chunks[i].size);
    }
}

int chunk_list_find(const Chunk_List *list, void* ptr)
{
    (void)list;
    (void) ptr;
    UNIMPLEMENTED();
    return -1;
}

void chunk_list_insert(const Chunk_List *list, void* ptr, size_t size)
{
    (void)list;
    (void)ptr;
    (void)size;
    UNIMPLEMENTED();
}

void chunk_list_remove(const Chunk_List *list, int index)
{
    (void)list;
    (void)index;
    UNIMPLEMENTED();
}




//*A void pointer is a pointer that has no associated data type with it. 
//*A void pointer can hold address of any type and can be typecasted to any type. 

//1. allocate memory
void *heap_alloc(size_t size)
{
    if(size>0)
    {
        //1. simple allocation
        //check boundary
        assert(heap_size+size<=HEAP_CAP);
        //allocate the space
        void *ptr=heap+heap_size;
        //update size
        heap_size += size;

        //2. update alloced chunk table


        //------ V0: ----------
        // Chunk chunk = {
        //     .start=ptr,
        //     .size = size
        // };

        // assert(heap_alloced_size+1<HEAP_ALLOCED_CAP);
        // heap_alloced[heap_alloced_size++]=chunk;
        //------ V0: ----------
        //---v1
        chunk_list_insert(&alloced_chunks, ptr, size);
        

        return ptr;
    }
    else
    return NULL;
}
    


//2. dellocate
//free memory
void heap_free(void *ptr)
{
    (void)ptr; 
    // //scan the alloced table to get empty space
    // for(size_t i=0; i<heap_alloced_size; ++i)
    // {
    //     if(heap_alloced[i].start==ptr)
    //     {
            
    //     }
    // }
    assert(false&&"TODO: heap free hasn't been implemented!");
}

//3.gc scan the pointer instead of heap itself
//maybe multi-thread
void heap_collect()
{
    assert(false&&"TODO: gc hasn't been implemented!");
}






int main()
{
    //v1. allocate 26 bytes
    // char* root = heap_alloc(26);
    // for(int i=0; i<26; i++)
    // {
    //     root[i]=i+'A';
    // }

    //v2 alloc a bunch of chunks
    //WARNING!: heap_alloc(0) is dump!
    for(int i=0; i<100; i++)
    {
        heap_alloc(i);
    }
    //chunk_list_dump();
    return 0;
}

