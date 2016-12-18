#include <stdio.h>
#include "../queue.h"

int main()
{
  SQueue *q;
  long data = 0;
  setNewQueue(q);
  if (!isEmpty(q)) goto err;
  if (popFromQueue(q, &data)) goto err;
  if (data != 0) goto err;
  if (!pushToQueue(q, 1)) goto err;
  if (!pushToQueue(q, 2)) goto err;
  if (!popFromQueue(q, &data)) goto err;
  if (data != 1) goto err;
  if (!popFromQueue(q, &data)) goto err;
  if (data != 2) goto err;
  if (popFromQueue(q, &data)) goto err;

  puts("All tests successful");
  return 0;
err:
  puts("Error");
  return 1;
}
