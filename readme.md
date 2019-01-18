# Przepływy
### Gabriela Ossowska
Dany jest graf opisujący pewną sieć wodociągową, w którym wierzchołki są oznaczone jako zawory, źródła lub punkty odbioru. Każdy zawór może być ustawiony na przepustowość w zakresie [0,1], każde źródło ma określoną wydajność, a odcinek stałą przepustowość w zakresie [0,1]. 
Opracować algorytm, który dla danych nastaw zaworów określi ilość wody docierającej do wszystkich punktów odbioru.

Ilość wody docierającej do ujść (punktów odbioru) można określić, używając algorytmu wyznaczania maksymalnego przepływu w sieci (grafie) po odpowiednim przygotowaniu grafu po dodaniu głównego źródła, głównego ujścia i rozdzieleniu zaworów na pary wierzchołków połączonych krawędzią o przepustowości równej nastawowi zaworu.


Założenie: więcej wody rozleje się tam, gdzie jest większa przepustowość, więc dla danej wydajności źródła i przepustowości krawędzi z niego wychodzących przepływ przez każdą krawędź jest proporcjonalny do jej przepustowości, a wszystkie przepływy sumują się do wydajności danego źródła. 

Program można uruchomić w dwóch trybach:
1. Czytanie grafu z pliku: graf [ścieżka do pliku]
2. Generowanie grafu: graf [liczba wierzchołków]

Liczba wierzchołków oznacza maksymalną liczbę wierzchołków danego typu, czyli osobno źródeł, zaworów i ujść.

#### Struktura pliku z grafem:
numer_żródła_1 wydajność_źródła_1 numer_żródła_2 wydajność_źródła_2 ... 
numer_zaworu_1 nastaw_zaworu_1 numer_zaworu_2 nastaw_zaworu_2 ...
numer_ujścia_1 numer_ujścia_2 ...

nr_wierzchołka_a nr_wierzchołka_b B nr_wierzchołka_c C ... 
nr_wierzchołka_d nr_wierzchołka_e E nr_wierzchołka_f F ... 
...

gdzie:
1. numery źródeł zaczynają się od 2 (0 i 1 zarezerwowane na główne źródło i ujście)
2. nr_wierzchołka_a nr_wierzchołka_b B nr_wierzchołka_c C 
    - oznacza, że z wierzchołka a jest krawędź do wierzchołka b o przepustowości B
    i do wierzchołka c o przepustowości C
    -wierzchołki końcowe krawędzi nie mogą być wcześniej podane jako źródła
3. wszystkie dane to liczby naturalne


#### Generacja 
1. Dodanie losowej liczby źródeł, zaworów i ujść (każdego rodzaju nie więcej, niż podano w argumencie wywołania).
2. Dodanie losowej liczby ścieżek od źródła do ujścia.
3. Stworzenie ścieżek: **losowe źródło -> zawór -> losowe ujście** dla każdego zaworu, który nie został przydzielony do żadnej ścieżki, oraz **losowe źródło -> ujście** dla każdego ujścia, które nie zostało przydzielone do żadnej ścieżki.

#### Wyjście
Program wypisuje wszystkie krawędzie utworzonego początkowego grafu z ich przepustowością, a po przejściu algorytmu krawędzie o niezerowym przepływie razem z przepływem i przepustowością.

Jeżeli program został uruchomiony w trybie generacji, to generuje tyle grafów, ile wyniósł argument wywołania, każdy z o jeden mniejszą maksymalną liczbą wierzchołków.
Na koniec podaje tabelę z przypisaniem czasu wykonania algorytmu do maksymalnej liczby wierzchołków.
