#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) \
{
    insert_at_tail(&(q->data), serialize(state));
}

struct game_state dequeue(struct queue *q) 
{ 
    return deserialize(remove_from_head(&(q->data)));
}

int number_of_moves(struct game_state start) 
{ 
    struct queue stateList;
    struct queue q;
    struct game_state childClass;
    struct game_state tempClass;
    struct list_node * lastNode;
    uint64_t classInt;
    (q.data.head) = NULL;
    (stateList.data.head) = NULL;
    int i;
    int j;
    int equality;
    enqueue(&q, start);
    while ((q.data.head) != NULL)
    {
        equality = 1;
        childClass = dequeue(&q);
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                if(childClass.tiles[i][j] != (4 * i + j + 1)%16)
                {
                    equality = 0;
                    i = 4;
                    j = 4;
                }
            }
        }
        if(equality)
        {
            free_list(q.data);
            free_list(stateList.data);
            return childClass.num_steps;
        }

        tempClass = childClass;
        tempClass.num_steps = 0;
        classInt = serialize(tempClass);
        if(stateList.data.head != NULL)
        {
            lastNode = stateList.data.head;
            while(lastNode -> next  != NULL && equality != 1)  
            {
                lastNode = lastNode -> next;
                if(classInt == lastNode->value) // ClassInt is the serialized version of the thing you just popped out of the queue 
                {
                    equality = 1;
                }
            }
            if(classInt == lastNode->value)
            {
                equality = 1;
            }
        }

        if(!equality) // Maybe remove if statement?
        {
            enqueue(&stateList, tempClass);

            if (childClass.empty_row != 3)
            {
                tempClass = childClass;
                move_up(&tempClass); // Move_up not working?
                enqueue(&q, tempClass);
            }
            if (childClass.empty_row != 0)
            {
                tempClass = childClass;
                move_down(&tempClass);
                enqueue(&q, tempClass);
            }
            if (childClass.empty_col != 3)
            {
                tempClass = childClass;
                move_left(&tempClass);
                enqueue(&q, tempClass);
            }
            if (childClass.empty_col != 0)
            {
                tempClass = childClass;
                move_right(&tempClass);
                enqueue(&q, tempClass);
            }
        }
    }
    return -1;
}
