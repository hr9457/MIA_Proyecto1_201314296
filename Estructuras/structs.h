#ifndef STRUCTS_H
#define STRUCTS_H

/*Estructura para una particion*/
struct partition
{
    char part_status[1];
    char part_type[1];
    char part_fit[1];
    int part_star;
    int part_size;
    char part_name[16];
};


/*Estructura para un MBR(Master Boot Record)*/
struct mbr
{
    int mbr_tamanio;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    char mbr_fit[1];
    partition mbr_partitionp[4];
};


#endif // STRUCTS_H
