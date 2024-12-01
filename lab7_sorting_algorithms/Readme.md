# Analiza Performanței Algoritmilor de Sortare

Pe baza rezultatelor, analizăm performanța fiecărui algoritm de sortare prin compararea timpilor de execuție și observăm cum aceștia scală odată cu creșterea dimensiunii vectorului. Vom discuta, de asemenea, comportamentul pentru diferite tipuri de input (Aleator, Sortat, Sortat invers).

---

## **1. Analiza Bubble Sort**

### Observații:
- Performanța Bubble Sort se degradează rapid pe măsură ce dimensiunea vectorului crește, consistent cu complexitatea sa \(O(N^2)\).
- Timpul de execuție crește aproximativ de 100 de ori atunci când dimensiunea vectorului se înzecește (de la \(N = 1000\) la \(N = 10000\)), reflectând creșterea de ordinul pătrat al timpului.
- Input-ul sortat performează mai bine în ceea ce privește numărul de swap-uri (0 swap-uri), dar numărul de comparații rămâne la cazul cel mai rău \(N(N-1)/2\), deoarece Bubble Sort nu se oprește mai devreme pentru vectorii complet sortați.

### Rezumat:
- **Cel mai bun caz (Sortat):** \(O(N^2)\) datorită comparațiilor complete, dar fără swap-uri.
- **Cel mai rău caz (Sortat invers):** \(O(N^2)\) cu număr maxim de comparații și swap-uri.
- Nu este practic pentru vectori mari datorită ratei lente de creștere.

---

## **2. Analiza Insertion Sort**

### Observații:
- Insertion Sort arată, de asemenea, o creștere pătratică odată cu creșterea dimensiunii vectorului, consistent cu complexitatea sa \(O(N^2)\).
- Totuși, este semnificativ mai rapid decât Bubble Sort pentru date aleatorii deoarece efectuează mai puține swap-uri și este, în general, mai eficient.
- În cazul sortat, performează excepțional (\(O(N)\)) deoarece face doar \(N-1\) comparații și fără swap-uri suplimentare.

### Rezumat:
- **Cel mai bun caz (Sortat):** \(O(N)\), ceea ce îl face eficient pentru date aproape sortate.
- **Cel mai rău caz (Sortat invers):** \(O(N^2)\) datorită numărului maxim de comparații și swap-uri.
- Practic pentru date mici sau aproape sortate, dar inadecvat pentru seturi de date mari aleatorii.

---

## **3. Analiza Merge Sort**

### Observații:
- Merge Sort performează constant bine pentru toate tipurile de input, cu timpi de execuție care scad logaritmic cu dimensiunea vectorului, conform așteptărilor pentru \(O(N \log N)\).
- Este semnificativ mai rapid decât Bubble și Insertion Sort pentru vectori mari (\(N = 10000\) și \(N = 100000\)).
- Performanța rămâne stabilă indiferent de tipul inputului (Aleator, Sortat, Sortat invers) deoarece Merge Sort nu depinde de ordinea inputului.

### Rezumat:
- **Cel mai bun, mediu și cel mai rău caz:** \(O(N \log N)\) pentru toate tipurile de input.
- Overhead ușor mai mare decât Quick Sort datorită necesității de memorie suplimentară pentru procesul de interclasare.
- Foarte eficient și stabil pentru vectori mari.

---

## **4. Analiza Quick Sort**

### Observații:
- Quick Sort este cel mai rapid algoritm dintre toate pentru toate dimensiunile și tipurile de vector analizate.
- Timpul de execuție scade logaritmic cu dimensiunea vectorului, conform așteptărilor pentru \(O(N \log N)\) în cazul mediu.
- Este semnificativ mai rapid decât Merge Sort datorită execuției in-place, evitând overhead-ul memoriei suplimentare.
- Performanța pentru vectori sortați este ușor mai slabă decât pentru inputuri aleatorii din cauza sensibilității la alegerile proaste de pivot, care pot duce la partiții dezechilibrate.

### Rezumat:
- **Cel mai bun și caz mediu:** \(O(N \log N)\), cu execuție foarte rapidă.
- **Cel mai rău caz (Sortat invers):** \(O(N^2)\) pentru alegeri proaste de pivot, deși acest lucru poate fi atenuat prin selecția pivotului aleator.
- Ideal pentru majoritatea scenariilor, în special pentru seturi mari de date, cu condiția ca selecția pivotului să fie eficientă.

---

## **5. Comparație între Algoritmi**

| Algoritm         | Complexitate     | Puncte forte                                | Puncte slabe                                |
|------------------|------------------|--------------------------------------------|--------------------------------------------|
| **Bubble Sort**  | \(O(N^2)\)       | Simplu de implementat.                     | Foarte lent pentru seturi mari de date.    |
| **Insertion Sort** | \(O(N^2)\)       | Eficient pentru date mici sau aproape sortate.| Performanță slabă pentru seturi mari.      |
| **Merge Sort**   | \(O(N \log N)\)  | Performanță constantă și stabilă.          | Necesită memorie suplimentară pentru interclasare. |
| **Quick Sort**   | \(O(N \log N)\)* | Extrem de rapid pe seturi mari.            | Performanță slabă în cazul cel mai rău fără optimizare. |

---

## **6. Recomandări Practice**

- **Seturi mici de date (e.g., \(N <= 1000\)):**
  - Utilizați **Insertion Sort** pentru date sortate sau aproape sortate.
  - Evitați **Bubble Sort** din cauza ineficienței.

- **Seturi mari de date (e.g., \(N >= 10000\)):**
  - Utilizați **Quick Sort** pentru viteză și consum redus de memorie.
  - Utilizați **Merge Sort** pentru scenarii care necesită sortare stabilă (e.g., elementele egale își păstrează ordinea relativă).

- **Cazuri speciale:**
  - Utilizați **Merge Sort** dacă overhead-ul memoriei nu este o problemă, deoarece este mai stabil decât Quick Sort.
  - Utilizați **Insertion Sort** pentru date aproape sortate datorită performanței liniare.

---

## **Concluzie**

Analiza confirmă complexitățile teoretice și evidențiază diferențele practice de performanță. În timp ce Bubble Sort și Insertion Sort sunt potrivite pentru seturi mici de date, Merge Sort și Quick Sort sunt superioare pentru seturi mari, Quick Sort fiind cel mai rapid dintre toate.
