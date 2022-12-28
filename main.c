#include<assert.h>
#include<stdbool.h>
#include<stdio.h>

//how many bites
#define HEAP_CAP 640000
//how many chunks
#define CHUNK_LIST_CAP 1024

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
    size_t count;
    Chunk chunks[CHUNK_LIST_CAP];
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
Chunk_List freed_chunks;


//print all chunks in chunk list
void chunk_list_dump(const Chunk_List* list)
{
    printf("Allocated Chunks (%zu):\n", list->count);
    for(size_t i=0; i<list->count; i++)
    {
        printf("    start: %p, size: %zu\n", list->chunks[i].start,
        list->chunks[i].size);
    }
}

int chunk_list_find(const Chunk_List *list, void* ptr)
{
    // (void)list;
    // (void) ptr;
    // UNIMPLEMENTED();
    for (size_t i = 0; i < list->count; ++i) {
        if (list->chunks[i].start == ptr) {
            return (int) i;
        }
    }
    return -1;
}

//insert chunk in chunklist( called  when alloc// or free(insert into freeded))
void chunk_list_insert(Chunk_List *list, void* start, size_t size)
{
    // insert the new chunk
    assert(list->count < CHUNK_LIST_CAP);
    list->chunks[list->count].start = start;
    list->chunks[list->count].size  = size;
    //sort the chunk list 
    for (size_t i = list->count;
            i > 0 && list->chunks[i].start < list->chunks[i - 1].start;
            --i) {
        const Chunk t = list->chunks[i];
        list->chunks[i] = list->chunks[i - 1];
        list->chunks[i - 1] = t;
    }
    list->count += 1;
}

void chunk_list_remove(Chunk_List *list, size_t index)
{
    assert(index < list->count);
    for (size_t i = index; i < list->count - 1; ++i) {
        list->chunks[i] = list->chunks[i + 1];
    }
    list->count -= 1;
    // (void)list;
    // (void)index;
    // UNIMPLEMENTED();
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
        //allocate the space: by moving the ptr forward
        void *ptr=heap+heap_size;
        //update size
        heap_size += size;
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
    // (void)ptr; 
     if (ptr != NULL) {
        const int index = chunk_list_find(&alloced_chunks, ptr);
        assert(index >= 0);
        assert(ptr == alloced_chunks.chunks[index].start);
        chunk_list_insert(&freed_chunks,
                          alloced_chunks.chunks[index].start,
                          alloced_chunks.chunks[index].size);
        chunk_list_remove(&alloced_chunks, (size_t) index);
    }
    // assert(false&&"TODO: heap free hasn't been implemented!");
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
    for(int i=0; i<20; i++)
    {
        void *p = heap_alloc(i);
        if(i%2==0)
            heap_free(p);
    }
    chunk_list_dump(&alloced_chunks);
    chunk_list_dump(&freed_chunks);
    return 0;
}

