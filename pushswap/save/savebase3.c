#include "pushswap.h"

void    radix_base4(t_push *push)
{
    int i;
    int max;
    int o;
    int k;
    int hun;

    push->stacka = base4_array(push);
    push->stackb = (char **) malloc (sizeof(char *) * push->asize);

    i = 0;
    max = max_base4(push->asize - 1);
    while (i < max)
    {
        // if (check_stack_f(push))
        //     return ;

        o = 0;
        k = howmany(push, 19 - i, '2');

            while (push->asize > 0 && (isthere(push, 19 - i, '0') || isthere(push, 19 - i, '1')))
            {
                if (((push->stacka[push->asize - 1]))[19 - i] == '1')
                {
                    cmd_pb(push);
                }
                if (((push->stacka[push->asize - 1]))[19 - i] == '0')
                {
                    cmd_pb(push);
                    if ((isthere(push, 19 - i, '0') || isthere(push, 19 - i, '1'))
                     && (((push->stacka[push->asize - 1]))[19 - i] == '2'))
                    {
                        cmd_rr(push);
                        o++;
                    }
                    else
                    {
                        if (push->bsize > 0)
                        {
                            cmd_rb(push, 1);
                        }
                    }
                }
                if (push->asize == 0 || !((isthere(push, 19 - i, '0') || isthere(push, 19 - i, '1'))))
                    break ;
                if (((push->stacka[push->asize - 1]))[19 - i] == '2')
                {
                    cmd_ra(push, 1);        
                    o++;
                }
            }

            if (push->asize > 1 && o != 0 && i != 0)
            {
                k = k % o;
                while (k--)
                    cmd_ra(push, 1); 
            }

        if (i == 0)
        {
            while ((isthere(push, 19 - i, '2')))
            {
                if (((push->stacka[push->asize - 1]))[19 - (i + 1)] == '2')
                {
                    cmd_ra(push, 1);
                }
                else
                {
                    cmd_pb(push);
                }
                if (!(isthere(push, 19 - (i + 1), '1')) && !(isthere(push, 19 - (i + 1), '0')) )
                {
                    break ;
                }
            }

            i++;   

            k = howmanyb(push, 19 - i, '1') + howmanyb(push, 19 - i, '0');
            o = 0;
            while (push->bsize > 0 && isthereb(push, 19 - i, '2'))
            {
                if (((push->stackb[push->bsize - 1]))[19 - i] == '2')
                {
                    cmd_pa(push);
                }
                else
                {
                    o++;
                    cmd_rb(push, 1);
                }
            }
            if (push->bsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }

            k = howmanyb(push, 19 - i, '0');
            o = 0;
            while (push->bsize > 0 && isthereb(push, 19 - i, '1'))
            {
                if (((push->stackb[push->bsize - 1]))[19 - i] == '1')
                {
                    cmd_pa(push);
                }
                else
                {
                    o++;
                    cmd_rb(push, 1);
                }
            }
            if (push->bsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }

            o = 0;
            while ((isthereb(push, 19 - i, '0')))
            {
                if (((push->stackb[push->bsize - 1]))[19 - (i + 1)] == '1')
                {
                    cmd_rb(push, 1);
                    o++;
                }
                else
                {
                    cmd_pa(push);
                }
                if (!(isthereb(push, 19 - (i + 1), '2')) && !(isthereb(push, 19 - (i + 1), '0')) )
                {
                    break ;
                }
            }

            k = push->bsize;
            if (push->bsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rb(push, 1); 
            }
        }

        if (i == max - 2 && push->asize > 0 && !(isthere(push, 19 - (max - 1), '2')))
        {
            i++;
            k = howmany(push, 19 - i, '1');
            o = 0;
            hun = 0;
            if (!isthere(push, 19 - i, '1'))
            {
                hun = push->asize;
            }
            while (push->asize > 0 && isthere(push, 19 - i, '0') && hun == 0)
            {
                if (((push->stacka[push->asize - 1]))[19 - i] == '0')
                {
                    cmd_pb(push);
                }
                else
                {
                    o++;
                    cmd_ra(push, 1);
                }
            }
            if (push->asize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_ra(push, 1); 
            }

            while (push->bsize > 0 && isthereb(push, 19 - i, '1'))
            {
                if (((push->stackb[push->bsize - 1]))[19 - (i - 1)] == '0')
                {
                    break ;
                }
                if (((push->stackb[push->bsize - 1]))[19 - i] == '1')
                {
                    cmd_pa(push);
                }
                else
                {
                    cmd_rb(push, 1);
                }
            }

            o = 0;
            while (push->bsize > 0 && ((push->stackb[push->bsize - 1]))[19 - (i - 1)] == '0')
            {
                if (((push->stackb[push->bsize - 1]))[19 - i] == '1')
                {
                    cmd_pa(push);
                    if (((push->stackb[push->bsize - 1]))[19 - i] == '1')
                    {
                        cmd_ra(push, 1);
                        o++;
                    }
                    else
                    {
                        if (!(((push->stackb[push->bsize - 1]))[19 - (i - 1)] == '0'))
                            break ;
                        cmd_rr(push);
                        o++;
                    }
                }
                else
                {
                    cmd_rb(push, 1);
                }
            }

            while(o--)
            {
                cmd_rra(push, 1);
            }
            while (hun--)
            {
                cmd_rra(push, 1);
            }

            while (push->bsize > 0 && isthereb(push, 19 - i, '0'))
            {
                if (((push->stackb[push->bsize - 1]))[19 - i] == '0')
                {
                    cmd_pa(push);
                }
                if (((push->stackb[push->bsize - 1]))[19 - (i - 1)] == '0')
                {
                    break ;
                }
            }

            while (push->bsize > 0)
            {
                if (push->bsize > 1)
                {
                    cmd_rrb(push, 1);
                    cmd_pa(push);
                }
                else
                {
                    cmd_pa(push);
                }
            }
            return ;
        }

        if (i < max - 2 && i >= 2)
        {
            o = 0;
            while ((isthereb(push, 19 - i, '0')) || (isthereb(push, 19 - i, '1')))
            {
                if ((isthereb(push, 19 - i, '1')))
                {
                    cmd_pa(push);
                }
                else
                {
                    if (((push->stackb[0]))[19 - (i + 1)] == '0')
                    {
                        o++;
                        cmd_rrb(push,1);
                    }
                    else
                    {
                        cmd_rrb(push,1);
                        cmd_pa(push);
                    }
                    if (!(isthereb(push, 19 - (i + 1), '1')) && !(isthereb(push, 19 - (i + 1), '2')))
                    {
                        break ;
                    }
                }
            }

            k = push->bsize;
            if (push->bsize > 1 && o != 0)
            {
                k = k % o;
                while (k--)
                    cmd_rrb(push, 1); 
            }
        }
        else
        {
            while (push->bsize != 0 && i != 0 && i != 1)
            {
                if ((isthereb(push, 19 - i, '1')))
                {
                    cmd_pa(push);
                }
                else if (push->bsize > 1)
                {
                    cmd_rrb(push,1);
                    cmd_pa(push);
                }
                else
                {
                    cmd_pa(push);
                }
            }
        }

        i++;
    }
                        //     int j;
                        // printf("\nstack a\n");
                        // j = push->asize;
                        // while (j--)
                        // {
                        //     printf("%s\n", (push->stacka[j]));
                        // }
                        // printf("\nstack b\n");
                        // j = push->bsize;
                        // while (j--)
                        // {
                        //     printf("%s\n", (push->stackb[j]));
                        // }
}   