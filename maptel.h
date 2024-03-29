#ifndef MAPTEL_H
#define MAPTEL_H

// Tworzy słownik i zwraca liczbę naturalną będącą jego identyfikatorem.
unsigned long maptel_create();

// Usuwa słownik o identyfikatorze id.
void maptel_delete(unsigned long id);

// Wstawia do słownika o identyfikatorze id informację o zmianie numeru
// tel_src na numer tel_dst. Nadpisuje ewentualną istniejącą informację.
void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst);

// Jeśli w słowniku o identyfikatorze id jest informacja o zmianie numeru
// tel_src, to ją usuwa. W przeciwnym przypadku nic nie robi.
void maptel_erase(unsigned long id, char const *tel_src);

// Sprawdza, czy w słowniku o identyfikatorze id jest zapisana zmiana numeru
// tel_src. Podąża ciągiem kolejnych zmian. Zapisuje zmieniony numer w tel_dst.
// Jeśli nie ma zmiany numeru lub zmiany tworzą cykl, to zapisuje w tel_dst
// numer tel_src. Wartość len to wielkość przydzielonej pamięci wskazywanej
// przez tel_dst.
void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len);

size_t TEL_NUM_MAX_LEN;

#endif
