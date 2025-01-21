#include "hls.h"

/* OPTIONS */

void opt_none_print();

/* print in single column */
void opt_column_print();

/* print details in single column
 *
 * the following information in documented in
 * `man 3 stat`
 * `info ls` (section: 10.1.2 What Information is Listed)
 *
 * type       hardlinks
 * |mode      | owner group  size time         name
 * ||________ | |____ |____  |___ |___________ |________
 * -rw-rw-r-- 1 chepe chepe  1928 Jan 17 14:22 README.md
 *
 * struct stat
 *    mode_t  st_mode  -> type and mode
 *    nlink_t st_nlink -> number of hardlinks
 *    uid_t   st_uid   -> single owner id (name has to be extracted)
 *    gid_t   st_gid   -> group owner id (name has to be extracted)
 *    off_t   st_size  -> size of file
 *    struct timespec
 *            st_mtim  -> time of last modification
 */
void opt_long_print();

/* print all . files */
void opt_all_print();

/* print all . files except ./ ../ */
void opt_almost_all_print();
