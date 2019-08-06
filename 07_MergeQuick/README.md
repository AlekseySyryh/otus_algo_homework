# Merge sort

## Алгоритмы

Classic - обычный Mergesort

Insert - начиная с определенного размера применяется Insert Sort

Parallel split - то же что и insert, но split выполняется параллельно

Run - поддержка run (аля TimSort)

Run parallel merge - Run с параллельным merge

## Быстродействие алгоритмов на разных датасетах, мс

### Случайный массив

Элементов|Classic|Insert|Parallel split|Run|Run parallel merge
---|---|---|---|---|---
10|0|0|0|0|0
100|0|0|0|0|0
1000|0|0|0|0|0
10000|0|0|0|0|1
100000|9|7|4|8|8
1000000|100|88|45|92|79
10000000|1039|912|481|1017|1092

### В отстортированном массиве 5 пар элеметов поменяли местами

Элементов|Classic|Insert|Parallel split|Run|Run parallel merge
---|---|---|---|---|---
10|0|0|0|0|0
100|0|0|0|0|0
1000|0|0|0|0|0
10000|0|0|0|0|0
100000|3|1|1|0|0
1000000|32|23|13|7|8
10000000|340|267|155|47|45

### В отстортированном массиве 5 пар элеметов поменяли местами, затем массив развернули

Элементов|Classic|Insert|Parallel split|Run|Run parallel merge
---|---|---|---|---|---
10|0|0|0|0|0
100|0|0|0|0|0
1000|0|0|0|0|0
10000|0|0|0|0|0
100000|2|2|1|0|1
1000000|32|25|15|15|14
10000000|351|280|163|162|163

### В отстортированном массиве 10% пар элеметов поменяли местами

Элементов|Classic|Insert|Parallel split|Run|Run parallel merge
---|---|---|---|---|---
10|0|0|0|0|0
100|0|0|0|0|0
1000|0|0|0|0|0
10000|0|0|0|0|1
100000|4|2|2|2|3
1000000|34|25|15|16|16
10000000|341|269|157|181|180

### В отстортированном массиве 10% пар элеметов поменяли местами, затем массив развернули

Элементов|Classic|Insert|Parallel split|Run|Run parallel merge
---|---|---|---|---|---
10|0|0|0|0|0
100|0|0|0|0|0
1000|0|0|0|0|0
10000|0|0|0|0|1
100000|3|3|2|4|4
1000000|34|27|15|34|37
10000000|352|281|162|368|377

## Выводы:

1. По идее классический алгоритм не должен зависить от порядка элементов. Тем страннее, что эту связь мы наблюдаем. 
Возможно причина в каких-то оптимизациях компилятора (а-ля branch prediction).

1. Insert вполне ожидаемо быстрее классического. Особенно эффект заметем на частичо отсортироывнном массиве, 
что логично - insert sort хорош именно на таких массивах. Не вполне понятно почему массив в обратном порядке оказывает 
такой незначительный эффект. 

1. Распаралеливанин split дает вполне ожидаемое ускорение чуть меньше x2 (сказываются накладные расходы на распаралеливание)

1. Run ожидаемо очень хорош для частично упорядоченных массивов. Очень хорошо наблюдается эффект снижения быстродействия 
на развернутом массиве, а также по мере снжения упорядоченности.

1. Parallel run не дал особого эффекта. Видимо бутылочное горлышко у алгоритма не в операции merge которая распараллеливалась 
в тестах, а в операции split, но рапаралелить ее (а вернее поиск Runов) не представляется возможным.

# Quick sort

## Алгоритмы

Все алгоримы в данной работе это quick сорт с различными модификациями. Опишем их.

Главная проблема у Quick sort - как выбирать поворотную точку (pivot). Хороший выбор точки - залог быстродействия алгоритма.
И наоборот плохая точка приведет к очень медленной работе. Идеальная точка - медиана сортируемого подмассива, но вычисление такой точки вычислительно неффективно.

Мы попробуем следующие варианты:

1. Classic - поворотная точка - последний элемент в массиве. Должно хорошо работать на случайных данных, но, к сожалению, плохо на упорядоченном массиве.

1. Median - медиана из трех элеменетов - первого, расположенного в середине и последнего. Должно работать хорошо, но можно подобрать наборы на которых будет работать плохо (хотя они и гораздо менее вероятны чем частично упорядоченные)

1. Random - случайный элемент. Должен работать хорошо, но все равно есть вероятность (хоть и незначительная), что работать будет плохо.

Кроме этого могут применяться (или не применяться) следующие модификации:

1. Insert - с определенного размера массива применить insert sort.

1. Parallel - распаралелливание

1. 3way - на шаге split делим массив не на две части (меньше и больше pivot), а на три (меньше, равно и больше, причем вторая после splita уже находится на месте). Должен дать выигрых на массивах с повтореним элементов.

1. Introsort - ни одна стратегия выбора pivotа (кроме медианы подмассива, но для ее применения нам нужно будет отсортироать 
массив, а если мы его отсортируем, то нам и pivot не сильно нужен) не снимает проблему вероятности выбора неудачной точки. 
Хотелось бы это проблему решить как-то по надежнее. Решение - если мы достигл определенной глубины рекурсии, видимо наша стратегия выбора точек не работает. Бросаем эту ерунду 
и применим пирамидальную сортировку с ее гарантированным временем выполнения.
 
Название алгоритма это стратегия выбора pivotа + используемые модификации.

## Быстродействие алгоритмов на разных датасетах, мс

Если алгоритм выполняется слишком долго и превысил глубину рекурсии - указывается прочерк.

### Все элементы различны

#### Случайный порядок

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|1|1|1|0|0|0|1|1|1|0|0|0|1|1|1|0|0|0|1|1|1|0|0|0|0|1|1|0|0|0|1|1|1|0|0|0|0|1|1|0|0|0|1|1|1|0|0|0
100000|11|11|13|6|6|6|19|16|20|7|7|7|11|12|13|8|8|8|17|17|20|8|8|9|11|11|15|6|6|6|18|16|21|7|7|7|11|11|13|8|8|8|17|17|20|9|8|9
1000000|124|126|143|74|74|80|188|173|212|85|77|82|132|128|149|104|100|103|196|193|211|98|93|100|124|122|148|79|77|83|193|170|208|78|75|80|130|127|146|98|96|102|183|182|206|97|93|101
10000000|1335|1499|1541|897|893|909|1912|1771|2163|871|812|881|1454|1513|1629|1187|1149|1192|1929|1876|2166|1092|996|1128|1372|1529|1563|898|894|908|1962|1785|2142|865|816|885|1448|1506|1632|1184|1151|1197|1945|1898|2142|1078|993|1098

#### В отстортированном массиве 5 пар элеметов поменяли местами

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|32|2|1|31|1|0|33|2|1|34|1|0|45|2|0|44|2|0|45|3|1|45|2|0|1|1|1|1|0|0|1|1|1|1|0|0|1|1|0|1|0|0|1|1|1|1|1|0
100000|-|43|9|-|36|2|-|56|17|-|39|3|-|56|7|-|58|2|-|66|14|-|59|4|12|15|9|12|9|2|13|17|15|12|9|3|15|14|7|15|10|3|15|17|14|15|10|3
1000000|-|120|89|-|21|33|-|125|168|-|26|48|-|81|95|-|28|46|-|132|161|-|32|61|154|210|177|154|109|126|153|215|221|155|116|130|177|167|180|176|114|138|179|215|212|178|117|143
10000000|-|1069|2447|-|246|1902|-|1348|3271|-|307|1957|-|734|3320|-|317|2785|-|1241|3904|-|351|2746|1856|2165|1640|1856|1348|1583|1856|2382|1551|1864|1406|1447|2126|1820|1857|2125|1405|1784|2123|2319|1658|2125|1442|1582

#### В отстортированном массиве 5 пар элеметов поменяли местами, затем массив развернули

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|16|0|0|16|0|0|18|1|1|18|0|0|24|0|0|23|0|0|24|1|1|24|0|0|0|0|1|0|0|0|0|1|1|0|0|0|1|0|0|1|0|0|1|1|1|1|0|0
100000|-|6|8|-|3|2|-|12|16|-|5|4|-|7|8|-|5|3|-|14|15|-|6|5|11|6|9|11|3|2|11|13|16|11|4|3|12|7|8|13|5|4|13|14|15|13|7|5
1000000|-|75|103|-|42|47|-|132|180|-|53|69|-|88|143|-|70|109|-|152|207|-|72|118|139|72|184|139|44|173|151|158|218|145|51|160|195|96|241|167|74|195|164|152|246|179|76|202
10000000|-|793|3400|-|521|2977|-|1367|4290|-|638|3010|-|1011|7312|-|864|7370|-|1557|8420|-|851|7014|1694|789|1893|1692|523|1818|1690|1360|1691|1693|636|1642|1934|1005|2900|1986|888|2891|1934|1557|2198|1938|855|2418

#### В отстортированном массиве 10% пар элеметов поменяли местами

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|0|0|1|0|0|0|2|1|1|0|0|0|0|0|0|0|0|0|1|1|1|0|0|0|1|0|1|0|0|0|2|1|1|1|0|0|1|0|0|1|0|0|2|1|1|1|0|0
100000|-|9|8|-|2|2|-|15|16|-|3|4|-|6|8|-|3|3|-|20|15|-|4|5|12|8|10|12|2|2|12|14|16|13|3|4|14|7|8|14|3|3|14|21|15|15|4|4
1000000|-|152|97|-|47|35|-|158|173|-|58|70|-|132|93|-|66|46|-|176|163|-|76|61|152|211|180|154|110|128|152|215|211|153|115|135|177|168|177|176|115|138|177|215|211|177|120|148
10000000|-|1045|2399|-|222|1863|-|1258|3164|-|279|2014|-|695|3223|-|281|2718|-|1203|3913|-|318|2944|1851|1035|1640|1852|220|1583|1854|1271|1542|1858|282|1476|2127|694|1851|2122|278|1782|2126|1202|1665|2128|323|1598

#### В отстортированном массиве 10% пар элеметов поменяли местами, затем массив развернули

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|0|0|1|0|0|0|1|1|1|0|0|0|0|0|0|0|0|0|1|1|1|0|0|0|1|0|0|0|0|0|2|1|1|0|0|0|1|0|0|0|0|0|2|1|1|0|0|0
100000|-|6|10|-|3|3|-|13|17|-|5|4|-|8|9|-|6|5|-|14|17|-|7|6|15|7|12|12|4|3|9|13|17|8|5|5|15|8|10|14|6|5|8|14|16|8|7|6
1000000|-|75|100|-|42|58|-|135|186|-|52|61|-|87|140|-|68|114|-|153|275|-|74|116|142|72|184|140|41|143|97|131|206|95|54|150|170|88|229|161|76|202|98|153|235|96|76|199
10000000|-|799|3391|-|521|3020|-|1398|4297|-|628|3047|-|1008|7618|-|861|7268|-|1564|8528|-|864|7125|1700|787|1861|1703|524|1823|1119|1392|1687|1114|636|1636|1935|1008|2887|1937|862|2851|1121|1574|2260|1122|854|2380

### Только 10% элементов различны

#### Случайный порядок

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|0|0|1|0|0|0|2|2|2|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|2|2|2|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100000|9|11|11|6|6|6|20|21|23|6|6|6|6|6|7|7|7|7|7|7|8|7|7|7|8|10|11|6|5|6|20|20|23|6|6|6|6|6|7|7|7|7|7|7|7|7|7|7
1000000|110|112|134|71|71|72|219|224|247|73|71|76|85|83|88|86|85|89|81|79|84|79|78|82|111|111|135|71|72|74|216|230|247|74|73|77|86|83|88|87|85|89|79|80|85|81|78|82
10000000|1258|1240|1462|874|856|883|2338|2263|2510|842|785|859|1039|1023|1081|1057|1042|1086|933|882|955|924|876|931|1229|1244|1465|868|858|877|2321|2289|2539|841|781|857|1036|1021|1080|1056|1043|1086|929|876|952|924|875|929

#### В отстортированном массиве 5 пар элеметов поменяли местами

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|14|0|0|14|0|0|15|2|2|15|0|0|4|1|0|4|1|0|4|1|0|4|1|0|1|1|0|1|0|0|1|1|2|1|0|0|1|0|0|1|0|0|1|1|0|1|1|0
100000|-|19|7|-|16|1|-|254|19|-|17|3|564|31|2|573|30|2|569|31|3|570|32|3|12|12|7|12|9|2|12|21|19|12|10|3|14|10|2|14|10|2|14|11|3|15|11|3
1000000|-|55|83|-|18|33|-|174|231|-|23|43|-|26|46|-|24|44|-|33|57|-|28|63|160|148|174|152|109|126|152|266|231|151|113|130|177|115|137|177|113|137|177|122|142|177|117|140
10000000|-|554|2413|-|225|1817|-|1713|3727|-|276|1877|-|273|2624|-|248|2665|-|305|2739|-|247|2731|1854|1676|1637|1852|1349|1580|1857|2832|1551|1852|1396|1468|2125|1396|1787|2126|1371|1780|2125|1427|1642|2127|1374|1648

#### В отстортированном массиве 5 пар элеметов поменяли местами, затем массив развернули

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|5|0|0|5|0|0|6|1|2|5|0|0|1|0|0|1|0|0|1|0|0|1|0|0|0|1|0|0|0|0|0|2|2|0|1|0|1|0|0|1|0|0|1|0|0|1|0|0
100000|-|6|7|-|3|2|-|19|20|-|6|3|154|3|3|153|3|3|152|4|4|155|4|3|12|14|8|12|12|2|12|10|20|12|11|3|12|3|3|13|3|3|13|4|4|13|4|3
1000000|-|72|96|-|50|50|-|205|224|-|68|58|-|44|100|-|45|91|-|49|101|-|47|101|147|162|179|147|144|136|144|269|251|146|159|140|161|44|190|160|46|184|160|48|187|159|46|187
10000000|-|968|3445|-|729|2861|-|2192|4619|-|883|3160|-|590|7105|-|607|7260|-|556|7179|-|554|7091|1793|2018|1868|1796|1837|1812|1759|3045|1666|1795|1980|1656|1928|592|2851|1933|614|2856|1930|555|2408|1928|561|2374

#### В отстортированном массиве 10% пар элеметов поменяли местами

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|0|0|0|0|0|0|2|2|2|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|1|0|1|0|0|2|2|2|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100000|-|6|8|-|2|2|-|17|20|-|3|3|520|3|3|519|2|3|521|3|4|520|3|3|12|6|8|12|2|2|12|17|20|12|3|4|14|2|3|14|2|3|14|3|4|14|3|4
1000000|-|57|85|-|20|32|-|178|215|-|25|44|-|22|44|-|21|47|-|28|56|-|25|50|154|148|172|152|112|126|153|265|229|153|116|133|177|22|139|178|21|135|177|27|145|179|24|137
10000000|-|552|2320|-|222|1894|-|1712|3678|-|273|2072|-|268|2589|-|242|2663|-|301|2939|-|243|2810|1931|584|1688|1914|224|1628|1882|1703|1537|1860|271|1481|2132|267|1784|2129|241|1781|2126|300|1627|2124|241|1655

#### В отстортированном массиве 10% пар элеметов поменяли местами, затем массив развернули

Элементов|Classic|Median|Random|Classic Insert|Median Insert|Random Insert|Classic Parallel|Median Parallel|Random Parallel|Classic Insert Parallel|Median Insert Parallel|Random Insert Parallel|Classic 3way|Median 3way|Random 3way|Classic Insert 3way|Median Insert 3way|Random Insert 3way|Classic Parallel 3way|Median Parallel 3way|Random Parallel 3way|Classic Insert Parallel 3way|Median Insert Parallel 3way|Random Insert Parallel 3way|Classic Intro|Median Intro|Random Intro|Classic Insert Intro|Median Insert Intro|Random Insert Intro|Classic Parallel Intro|Median Parallel Intro|Random Parallel Intro|Classic Insert Parallel Intro|Median Insert Parallel Intro|Random Insert Parallel Intro|Classic 3way Intro|Median 3way Intro|Random 3way Intro|Classic Insert 3way Intro|Median Insert 3way Intro|Random Insert 3way Intro|Classic Parallel 3way Intro|Median Parallel 3way Intro|Random Parallel 3way Intro|Classic Insert Parallel 3way Intro|Median Insert Parallel 3way Intro|Random Insert Parallel 3way Intro
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
10|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
1000|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
10000|0|0|0|0|0|0|1|2|2|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|2|2|2|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
100000|-|6|8|-|3|3|-|19|21|-|5|4|98|3|4|98|4|4|110|4|5|107|4|5|13|14|8|12|12|3|8|11|20|8|13|4|13|3|3|13|4|4|7|4|5|7|4|5
1000000|-|75|94|-|49|46|-|205|224|-|71|59|-|46|97|-|48|87|-|49|107|-|48|98|148|166|183|147|143|144|98|278|237|95|161|148|163|47|185|162|48|190|98|48|188|97|48|190
10000000|-|954|3418|-|715|3088|-|2199|4684|-|869|2958|-|603|6848|-|617|7075|-|556|7068|-|556|6994|1774|2017|1862|1767|1830|1815|1124|3045|1672|1123|1970|1629|1934|591|2850|1941|614|2843|1130|554|2450|1129|551|2421


## Выводы

По алгоритмам выбора pivot:

1. Алгоритм Classic хорошо себя ведет на случайных данных. Иногда на этих 
наборах он переигрывает конкурентов, т.к. имеет меньшие накладные расходы. 
К сожалению очень плохо себя ведет на упорядоченных данных. Поскольку в
реальных задачах такие наборы вполне возможны, использовать такой алгоритм 
на практике не следует. 

1. Алгоритм Median очень показал себя очень хорошо, особенно на больших 
объемах данных, где он переиграл Random. Минус алгоритма в том что несмотря 
на то что "плохие" наборы данных для него не так очевидны, но они очевидно 
есть, и в силу детерменированной природы алгоритма некий злоумышленник 
может такой набор подобрать. Рекомендуется использовать совместно с 
дополнительными мерами против "плохих наборов".

1. Алгоритм Random показал себя неплохо. Да он несколько хуже чем Median, 
и тоже имеет "плохие наборы", но в силу его стохастической природы подобрать 
набор заранее невозможно. Хотя есть крайне небольшая вероятность что "плохим
набором" станет любой, на практике такой вероятностью можно пренебречь.

Прочие модификации:

1. Insert - Однозначно дает улучшение, ведь InsertSort на небольших массивах работает гораздо быстрее чем QuickSort.

1. Parallel - Несмотря на теоретическую возможность, реального улучшения не дает. 
По видимому, причина здесь в том что распаралеливаемая операция достаточно легкая и выигрыш не превышает накладных расходов на распаралеливание.
Также следует отметить что неудачный выбор Pivota (от чего мы не застрахованы) так-же сведет выигрыш от распаралеливания к нулю (а то и в минус).

1. 3way - Если в алгоритме нет дублей - дает небольшой проигрыш (т.к. имеет большие накладные расходы), но если они есть дает очень серьезный выигрыш, и чем больше дублей тем больше выигрыш.

1. Introsort - Очень хорошая модификация. Полностью устраняет проблему "плохих наборов", при этом замедление работы на хороших наборах крайне незначительное.

По итогу лучшим вариантом я считаю алгоритм Median Insert 3way Intro.