# Projekt 2 - Práce s datovými strukturami

## Popis projektu
Vytvořte program, který implementuje jednoduchou shlukovou analýzu, metodu nejbližšího souseda (angl. single linkage).

Smyslem projektu není studium shlukových analýz. Pro projekt bude stačit následující popis (zdroj Wikipedia): Shluková analýza (též clusterová analýza, anglicky cluster analysis) je vícerozměrná statistická metoda, která se používá ke klasifikaci objektů. Slouží k třídění jednotek do skupin (shluků) tak, že jednotky náležící do stejné skupiny jsou si podobnější než objekty z ostatních skupin.

Shlukovou analýzu provádějte na dvourozměrných objektech. Každý objekt je identifikován celým číslem. Objekty jsou uloženy v textovém souboru.

Při implementaci můžete pro vizualizaci a porozumění objektů používat tuto jednoduchou aplikaci, která vykresluje a obarvuje vámi vygenerované shluky.

### Metoda nejbližšího souseda
Metoda nejbližšího souseda vybírá ke spojení vždy dva shluky, které mají k sobě nejblíže. Vzdálenost dvou shluků je rovna nejmenší vzdálenosti libovolných dvou objektů z obou shluků.

## Detailní specifikace
### Překlad a odevzdání zdrojového souboru
Odevzdání: Program implementujte ve zdrojovém souboru cluster.c. Zdrojový soubor odevzdejte prostřednictvím informačního systému.

Překlad: Program bude překládán s následujícími argumenty

$ gcc -std=c99 -Wall -Wextra -Werror -DNDEBUG cluster.c -o cluster -lm
Definice makra NDEBUG (argument -DNDEBUG) je z důvodu anulování efektu ladicích informací.

Propojení s matematickou knihovnou (argument -lm) je z důvodu výpočtu vzdálenosti objektů.

### Syntax spuštění
Program se spouští v následující podobě:

./cluster SOUBOR [N]
Argumenty programu:

SOUBOR je jméno souboru se vstupními daty.

N je volitelný argument definující cílový počet shluků. N > 0. Výchozí hodnota (při absenci argumentu) je 1.

### Implementační detaily
Formát vstupního souboru
Vstupní data jsou uložena v textovém souboru. První řádek souboru je vyhrazen pro počet objektů v souboru a má formát:

count=N
kde číslo je počet objektů v souboru. Následuje na každém řádku definice jednoho objektu. Počet řádků souboru odpovídá minimálně počtu objektů + 1 (první řádek). Další řádky souboru ignorujte. Řádek definující objekt je formátu:

OBJID X Y
kde OBJID je v rámci souboru jednoznačný celočíselný identifikátor, X a Y jsou souřadnice objektu také celá čísla. Platí 0 <= X <= 1000, 0 <= Y <= 1000.

1. podúkol
Stáhněte si kostru programu cluster.c. Seznamte se s datovými typy a funkcemi. Vaším úkolem je pouze doplnit kód na místech označených komentářem TODO.

2. podúkol
Načítání vstupního souboru a následný výpis:

1. Implementujte funkce:

void init_cluster(struct cluster_t *c, int cap);
void clear_cluster(struct cluster_t *c);
void append_cluster(struct cluster_t *c, struct obj_t obj);
int load_clusters(char *filename, struct cluster_t **arr);
Funkce init_cluster slouží pro inicializaci shluku (alokaci požadovaného místa).

Funkce clear_cluster slouží pro odstranění všech objektů ve shluku (dealokaci místa) a reinicializaci shluku s kapacitou 0.

Funkce append_cluster slouží pro přidání objektu na konec shluku.

Funkce load_clusters načítá ze vstupního souboru všechny objekty a ukládá je každý do jednoho shluku. Shluky budou uloženy v poli. Místo pro pole shluků musí funkce alokovat.

2. Ověřte funkcionalitu na načtení vstupního souboru (pomocí vámi implementované funkce load_clusters) a následném výpisu (pomocí funkce print_clusters):