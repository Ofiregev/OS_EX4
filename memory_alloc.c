#include <stdio.h>
#define HEAP_TOTAL_SIZE 2048

typedef struct Memory_Node
{
    __uint32_t size;
    __uint8_t used;
    struct Memort_Node* nextNode;
    struct Memory_Node* prevNode;
}mem,*pmem;

static unsigned char MyHeapArea[HEAP_TOTAL_SIZE];
static pmem heapStart = (pmem) MyHeapArea; 

void memory_init()
{
    heapStart = (pmem) MyHeapArea;
    heapStart->size = HEAP_TOTAL_SIZE - sizeof(mem);
    heapStart->nextNode = NULL;
    heapStart->prevNode = NULL;
}
void * my_malloc(size_t size)
{
  pmem currentHeapBlock;
  pmem bestHeapBlock;
  __uint32_t bestHeapBlockSize;

  /* init current block to start of heap */
  currentHeapBlock = heapStart;
  /* init best heap block */
  bestHeapBlock = (pmem) NULL;
  bestHeapBlockSize = HEAP_TOTAL_SIZE + 1; /* init with invalid size */

  while (currentHeapBlock)
  {
    /* check if current block matches and fittest best (so far) */
    if ( (!currentHeapBlock->used) &&(currentHeapBlock->size >= (size + sizeof(mem))) &&(currentHeapBlock->size <= bestHeapBlockSize) )
    {
      bestHeapBlock = currentHeapBlock;
      bestHeapBlockSize = currentHeapBlock->size;
    }

    currentHeapBlock = currentHeapBlock->nextNode;
  }

  if (bestHeapBlock != NULL)
  {
    pmem heapNodeAllocate;

    /* found a matching block, split it up and return the top of the memory area to the user */
    /* the best matching block is decreased by the needed memory area*/
    bestHeapBlock->size = bestHeapBlock->size - size - sizeof(mem);
    /* new heap node is after the current heap + the size of its control data + allocated memory size */
    heapNodeAllocate = (pmem)(((unsigned char*)bestHeapBlock) + sizeof(mem) + bestHeapBlock->size);
    heapNodeAllocate->size = size;
    heapNodeAllocate->used = 1;
    heapNodeAllocate->nextNode = bestHeapBlock->nextNode;
    heapNodeAllocate->prevNode = bestHeapBlock;
    if (bestHeapBlock->nextNode != NULL)
    {
      /* next block exists */
      pmem temp = bestHeapBlock->nextNode;
      temp->prevNode = heapNodeAllocate;
    }
    bestHeapBlock->nextNode = heapNodeAllocate;
    /* return pointer to memory of new heap node after control data */
    return (void*)((unsigned char*)heapNodeAllocate + sizeof(mem));
  }
  return (void*) NULL;
}
void memory_free(void* p)
{
  if (p == NULL)
  {
    return;
  }

  /* get actual heap node */
  pmem currentBlock = (pmem)((unsigned char*)p - sizeof(mem));
  printf("p is %p\n",p);
    printf("curblock is: %p\n",currentBlock);


  if (currentBlock == NULL)
  {
    return;
  }

  currentBlock->used = 0;

  /* check if we can merge with next block */
  pmem temp = currentBlock->nextNode;
  printf("temp is: %p\n",temp);
  if (temp != NULL)
  {
    if (!temp->used)
    {
      /* add size of next block and its control data to current block */
      currentBlock->size += temp->size;
      currentBlock->size += sizeof(mem);

      /* remove next block */
      /* link current block to next-next block */
      currentBlock->nextNode = temp->nextNode;
      /* link next-next block to current block if next-next block exists */
      if (currentBlock->nextNode != NULL) /* currentBlock->nextNode points to next-next block already! */
      {
        temp->prevNode = currentBlock;
      }
    }
  }
printf("cur prev: %p",currentBlock->prevNode);
  /* check if we can merge with previous block */
  if (currentBlock->prevNode != NULL)
  {
    if (!currentBlock->prevNode->used)
    {
        printf("used, %d\n",currentBlock->prevNode->used);
      /* add size of freed memory region and its control data to previous block */
      currentBlock->prevNode->size += currentBlock->size;
      currentBlock->prevNode->size += sizeof(mem);

      /* remove freed block from list */
      /* link previous block to next block */
      currentBlock->prevNode->nextNode = currentBlock->nextNode;
      /* link next block to previous block if next block exists */
      if (currentBlock->nextNode != NULL)
      {
        temp->prevNode = currentBlock->prevNode;
      }
      p = temp;
    }
  }
  return;
} 

int main(int argc, char const *argv[])
{
    char * m ;
    char * t;
    memory_init();
    printf("%p\n",m);
    m = (char*) my_malloc(10);
    t = (char *) my_malloc(200);
    m ="acv";

    if(!m){
        printf("error");
    }else{
        printf("yofi!\n");
      
    }

    if(!t){
        printf("error");
    }else{
        printf("yofi!\n");
      
    }
    printf("%p\n",m);
    memory_free(m);
    printf("%p\n",m);
    return 0;
}
