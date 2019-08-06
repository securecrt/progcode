int comp(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int i, j, k,l, sum;
    int **ret;
    int *block;
    int pre_alloc_size = 64;
    *returnSize = 0;
    ret = NULL;
    *returnColumnSizes = NULL;
    ret = (int **)malloc(pre_alloc_size * sizeof(int **));

    block = (int *)malloc(pre_alloc_size*3*sizeof(int));
    for(l=0;l<pre_alloc_size;l++)
        ret[l] = &block[l*3];
    
    i = 0;
    j = 0;
    k = 0;
    qsort(nums, numsSize, sizeof(int), comp);
    if (numsSize < 3)
        return NULL;

    for (i = 0; i < numsSize - 2; i++)
    {

        if (nums[i] > 0)
            break;
        if (i >= 1 && nums[i] == nums[i - 1])
            continue;
        j = i + 1;
        k = numsSize - 1;
        while (j < k)
        {
            sum = nums[i] + nums[j] + nums[k];
            if (sum == 0)
            {
                ret[*returnSize][0] = nums[i];
                ret[*returnSize][1] = nums[j];
                ret[*returnSize][2] = nums[k];
                *returnSize = *returnSize + 1;

                while (j < k && nums[j] == nums[j + 1])
                    j++;
                while (j < k && nums[k] == nums[k - 1])
                    k--;
                j++, k--;
            }
            else if (sum > 0)
                k--;
            else
                j++;
            if ((*returnSize) == pre_alloc_size)
            {
                pre_alloc_size = pre_alloc_size *2 ;
                ret = (int **)realloc(ret, pre_alloc_size * sizeof(int **));
                block = (int *)malloc((pre_alloc_size-(*returnSize))*3*sizeof(int));
                for(l=0;l<pre_alloc_size-(*returnSize);l++)
                    ret[l+(*returnSize)] = &block[l*3];
            }
        }
    }
    *returnColumnSizes = (int *)malloc((*returnSize) * sizeof(int));
    for (i = 0; i < (*returnSize); i++)
        (*returnColumnSizes)[i] = 3;
    return ret;
}