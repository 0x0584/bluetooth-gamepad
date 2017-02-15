#ifndef G_TYPES_H
#define G_TYPES_H

/* just because C has no bool-type, doesn't mean that
 * they did not think of it. but instead, you have 
 * to understand the philosophy of C in order to get
 * the idea...
 */
typedef enum ENUM_BOOL_TYPE {
  false = (1==0), 
  true  = !false
} bool;

typedef struct GAMEPAD gpad_t;
typedef struct GAMEPAD_BUTTON gpad_butn;
typedef struct GAMEPAD_AXE gpad_axe;
typedef struct GAMEPAD_INFO gpad_info;
  
#endif	/* G_TYPES_H */
