struct qNode_s
{
    struct qNode_s *next,
    struct qNode_s *prev,
    data long
}

typedef struct qNode_s qNode;

struct Queue_s
{
    struct qNode_s *head,
    struct qNode_s *tail
} Queue_default = {NULL, NULL}

typedef struct Queue_s Queue;