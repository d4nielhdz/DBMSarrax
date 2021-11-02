#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./definitions.c"

typedef struct student
{
    char nombre[COL_SIZE], apellido[COL_SIZE], carrera[COL_SIZE], semestre[COL_SIZE], matricula[COL_SIZE];
} Student;

typedef struct calificaciones
{
    char materia[COL_SIZE], matricula[COL_SIZE], calificacion[COL_SIZE];
} Grades;

int main()
{
    FILE *archivoAlumno;
    FILE *archivoCalificaciones;
    int menu = 1, aux;

    while (menu != 0)
    {
        printf("Menu: \n 1) Select all \n 2) Select con condicion \n 3) Insertar \n 4) Borrar \n 5) Join \n 0) Salir \n");
        scanf("%d", &menu);

        if (menu == 1)
        {
            int op;
            FILE *fp;
            printf("Elija la tabla para imprimir \n 1) Students \n 2) Grades \n");
            scanf("%d", &op);
            switch (op)
            {
            case 1:;
                Student *a;
                a = (Student *)malloc(sizeof(Student));
                fp = fopen(STUDENTS_TABLE, "rb");
                while (fread(a, sizeof(Student), 1, fp))
                {
                    printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s \n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula);
                }
                fclose(fp);
                break;

            case 2:;
                Grades *c;
                c = (Grades *)malloc(sizeof(Grades));
                fp = fopen(GRADES_TABLE, "rb");
                while (fread(c, sizeof(Grades), 1, fp))
                {
                    printf("Materia: %s Matricula: %s Calificacion: %s \n", c->materia, c->matricula, c->calificacion);
                }
                fclose(fp);
                break;
            }
        }
        else if (menu == 2)
        {
            printf("Elija la tabla en la cual quiere hacer el select: \n 1) Alumnos \n 2) Grades \n");
            scanf("%d", &aux);
            switch (aux)
            {
            case 1:
                int op;
                char *aux = malloc(1024);
                FILE *fp;
                Student *a;
                fp = fopen(STUDENTS_TABLE, "rb");
                printf("Elija la columna para hacer la condicion \n 1) Nombre \n 2) Apellido \n 3) Carrera \n 4) Semestre \n 5) Matricula \n");
                scanf("%d", &op);

                switch (op)
                {
                case 1:
                    printf("Teclee el nombre\n");
                    scanf("%s", aux);
                    a = (Student *)malloc(sizeof(Student));
                    while (fread(a, sizeof(Student), 1, fp))
                    {
                        if (strcmp(a->nombre, aux) == 0)
                        {
                            printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s \n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula);
                        }
                    }
                    break;
                case 2:
                    printf("Teclee el apellido\n");
                    scanf("%s", aux);
                    a = (Student *)malloc(sizeof(Student));
                    while (fread(a, sizeof(Student), 1, fp))
                    {
                        if (strcmp(a->apellido, aux) == 0)
                        {
                            printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s \n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula);
                        }
                    }
                    break;
                case 3:
                    printf("Teclee el carrera\n");
                    scanf("%s", aux);
                    a = (Student *)malloc(sizeof(Student));
                    while (fread(a, sizeof(Student), 1, fp))
                    {
                        if (strcmp(a->carrera, aux) == 0)
                        {
                            printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s \n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula);
                        }
                    }
                    break;
                case 4:
                    printf("Teclee el semestre\n");
                    scanf("%s", aux);
                    a = (Student *)malloc(sizeof(Student));
                    while (fread(a, sizeof(Student), 1, fp))
                    {
                        if (strcmp(a->semestre, aux) == 0)
                        {
                            printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s \n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula);
                        }
                    }
                    break;
                case 5:
                    printf("Teclee la matricula\n");
                    scanf("%s", aux);
                    a = (Student *)malloc(sizeof(Student));
                    while (fread(a, sizeof(Student), 1, fp))
                    {
                        if (strcmp(a->matricula, aux) == 0)
                        {
                            printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s \n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula);
                        }
                    }
                    break;
                }
                fclose(fp);
                break;
            case 2:
                int op;
                char *aux = malloc(1024);
                FILE *fp;
                Grades *c;
                fp = fopen(GRADES_TABLE, "rb");
                printf("Elija la columna para hacer la condicion \n 1) Materia \n 2) Matricula \n 3) Calificacion \n");
                scanf("%d", &op);

                switch (op)
                {
                case 1:
                    printf("Teclee la materia\n");
                    scanf("%s", aux);

                    c = (Grades *)malloc(sizeof(Grades));
                    while (fread(c, sizeof(Grades), 1, fp))
                    {
                        if (strcmp(c->materia, aux) == 0)
                        {
                            printf("Materia: %s Matricula: %s Calificacion: %s \n", c->materia, c->matricula, c->calificacion);
                        }
                    }
                    break;
                case 2:
                    printf("Teclee la matricula\n");
                    scanf("%s", aux);
                    c = (Grades *)malloc(sizeof(Grades));
                    while (fread(c, sizeof(Grades), 1, fp))
                    {
                        if (strcmp(c->matricula, aux) == 0)
                        {
                            printf("Materia: %s Matricula: %s Calificacion: %s \n", c->materia, c->matricula, c->calificacion);
                        }
                    }
                    break;
                case 3:
                    printf("Teclee la calificacion\n");
                    scanf("%s", aux);
                    c = (Grades *)malloc(sizeof(Grades));
                    while (fread(c, sizeof(Grades), 1, fp))
                    {
                        if (strcmp(c->calificacion, aux) == 0)
                        {
                            printf("Materia: %s Matricula: %s Calificacion: %s \n", c->materia, c->matricula, c->calificacion);
                        }
                    }
                    break;
                }
                break;
            }
        }
        else if (menu == 3)
        {
            int op;
            FILE *fp;
            char *p = malloc(1024);
            Student *a;
            a = (Student *)malloc(sizeof(Student));
            Grades *c;
            c = (Grades *)malloc(sizeof(Grades));

            printf("Elija la tabla para hacer insert \n 1) Alumnos \n 2) Grades \n");
            scanf("%d", &op);
            switch (op)
            {
            case 1:

                fp = fopen(STUDENTS_TABLE, "ab");

                printf("Enter Student name\n");
                scanf("%s", p);
                strcpy(a->nombre, p);
                fflush(stdin);

                printf("Enter Student lastname\n");
                scanf("%s", p);
                strcpy(a->apellido, p);
                fflush(stdin);

                printf("Enter Student carrer\n");
                scanf("%s", p);
                strcpy(a->carrera, p);
                fflush(stdin);

                printf("Enter Student semester\n");
                scanf("%s", p);
                strcpy(a->semestre, p);
                fflush(stdin);

                printf("Enter Student id\n");
                scanf("%s", p);
                strcpy(a->matricula, p);
                fflush(stdin);

                fwrite(a, sizeof(Student), 1, fp);

                fclose(fp);

                break;

            case 2:
                fp = fopen(GRADES_TABLE, "ab");
                printf("Enter Course name\n");
                scanf("%s", p);
                strcpy(c->materia, p);
                fflush(stdin);

                printf("Enter Student id\n");
                scanf("%s", p);
                strcpy(c->matricula, p);
                fflush(stdin);

                printf("Enter Course grade\n");
                scanf("%s", p);
                strcpy(c->calificacion, p);
                fflush(stdin);

                fwrite(c, sizeof(Grades), 1, fp);

                fclose(fp);

                break;
            }
        }
        else if (menu == 4)
        {
            int op;
            char *id = malloc(1024);
            FILE *fp;
            FILE *temp;
            printf("Elija la tabla para hacer delete \n 1) Alumnos \n 2) Grades \n");
            scanf("%d", &op);
            switch (op)
            {
            case 1:
                printf("Ingrese la matricula que quiera eliminar:\n");
                scanf("%s", id);
                Student *a;
                a = (Student *)malloc(sizeof(Student));
                fp = fopen(STUDENTS_TABLE, "rb");
                temp = fopen("tmp.bin", "wb");
                while (fread(a, sizeof(Student), 1, fp))
                {
                    if (strcmp(a->matricula, id) == 0)
                    {
                        printf("The row has been deleted.\n\n");
                    }
                    else
                    {
                        fwrite(a, sizeof(Grades), 1, temp);
                    }
                }
                fclose(fp);
                fclose(temp);

                remove(STUDENTS_TABLE);
                rename("tmp.bin", STUDENTS_TABLE);

                break;

            case 2:
                printf("Ingrese la matricula que quiera eliminar:\n");
                scanf("%s", id);
                Grades *c;
                c = (Grades *)malloc(sizeof(Grades));
                fp = fopen(GRADES_TABLE, "rb");
                temp = fopen("tmp.bin", "wb");
                while (fread(c, sizeof(Grades), 1, fp))
                {
                    if (strcmp(c->matricula, id) == 0)
                    {
                        printf("The row has been deleted.\n\n");
                    }
                    else
                    {
                        fwrite(a, sizeof(Grades), 1, temp);
                    }
                }
                fclose(fp);
                fclose(temp);

                remove(GRADES_TABLE);
                rename("tmp.bin", GRADES_TABLE);

                break;
            }
        }
        else if (menu == 5)
        {
            FILE *fpStudents;
            FILE *fpGrades;
            char *aux = malloc(1024);
            Student *a;
            a = (Student *)malloc(sizeof(Student));
            Grades *c;
            c = (Grades *)malloc(sizeof(Grades));

            fpStudents = fopen(STUDENTS_TABLE, "rb");

            printf("Teclee la matricula\n");
            scanf("%s", aux);
            while (fread(a, sizeof(Student), 1, fpStudents))
            {
                if (strcmp(a->matricula, aux) == 0)
                {
                    fpGrades = fopen(GRADES_TABLE, "rb");
                    while (fread(c, sizeof(Grades), 1, fpGrades))
                    {
                        if (strcmp(c->matricula, aux) == 0)
                        {
                            printf("Nombre: %s Apellido: %s Carrera: %s Semestre: %s Matricula: %s Materia: %s Calificacion: %s \n\n", a->nombre, a->apellido, a->carrera, a->semestre, a->matricula, c->materia, c->calificacion);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
