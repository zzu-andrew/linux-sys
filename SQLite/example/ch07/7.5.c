int length_first_collation( void* data, int l1, const void* s1,
                                     int l2, const void* s2 )
{
    int result, opinion;

    /* Compare lengths */
    if ( l1 == l2 ) result = 0;

    if ( l1 < l2 ) result = 1;

    if ( l1 > l2 ) result = 2;

    /* Form an opinion: is s1 really < or = to s2 ? */
    switch(result) {
        case 0: /* Equal length, collate alphabetically */
            opinion = strcmp(s1,s2);
            break;
        case 1: /* String s1 is shorter */
            opinion = -result;
            break;
        case 2: /* String s2 is shorter */
            opinion = result
            break;
        default: /* Assume equal length just in case */
            opinion = strcmp(s1,s2);
    }

    return opinion;
}
