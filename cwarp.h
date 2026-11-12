// Name of the library
#ifndef CWARP_H
#define CWARP_H

// Go back to a certain point
#define checkpoint(name) checkpoint_##name:
#define go_back(name)    goto checkpoint_##name

// Skip ahead to a certain point
#define skip_to(name)    goto skip_##name
#define skip_point(name) skip_##name:

#endif
