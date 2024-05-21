#ifndef _MAIN_H
#define _MAIN_H

#define REDIRECT_FUNCTION(a, f) _sw(0x08000000 | (((u32)(f) >> 2) & 0x03FFFFFF), a); _sw(0x00000000, a + 4);

int sceKernelCallSubIntrHandler(int unk1, u32 unk2, int unk3, int unk4);
int sceUmdCheckMedium (void);

#endif /* _MAIN_H */