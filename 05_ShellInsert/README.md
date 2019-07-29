# Отсортированный массив, 5 пар элементов поменяны местами

Записей|Insert sort|Shell sort (Shell, 1959)|Shell sort (Frank & Lazarus, 1960)|Shell sort (Hibbard, 1963)|Shell sort (Papernov & Stasevich, 1965)|Shell sort (Pratt, 1971)|Shell sort (Pratt, 1971, Knuth, 1973)|Shell sort (Incerpi & Sedgewick, 1985, Knuth)|Shell sort (Sedgewick, 1982)|Shell sort (Sedgewick, 1986)|Shell sort (Gonnet & Baeza-Yates, 1991)|Shell sort (Tokuda, 1992)|Shell sort (Ciura, 2001, Dovgopol, 2011)
---|---|---|---|---|---|---|---|---|---|---|---|---|---
20|0|0|0|0|0|0|0|0|0|0|0|0|0
40|0|0|0|0|0|0|0|0|0|0|0|0|0
80|0|0|0|0|0|0|0|0|0|0|0|0|0
160|0|0|0|0|0|0|0|0|0|0|0|0|0
320|0|0|0|0|0|0|0|0|0|0|0|0|0
640|0|0|0|0|0|0|0|0|0|0|0|0|0
1280|0|0|0|0|0|0|0|0|0|0|0|0|0
2560|0|0|0|0|0|0|0|0|0|0|0|0|0
5120|0|0|1|0|0|2|0|0|1|0|0|0|0
10240|0|0|0|0|1|6|0|0|0|0|0|0|0
20480|0|2|2|3|2|15|2|1|1|3|2|2|1
40960|1|5|6|6|6|35|4|4|3|6|4|5|4
81920|2|14|13|14|14|83|9|10|8|12|12|13|8
163840|4|27|27|28|30|177|18|22|16|24|26|28|16
327680|10|59|60|63|64|402|42|47|36|54|53|49|33

# Отсортированный массив, 10% пар элементов поменяны местами

Записей|Insert sort|Shell sort (Shell, 1959)|Shell sort (Frank & Lazarus, 1960)|Shell sort (Hibbard, 1963)|Shell sort (Papernov & Stasevich, 1965)|Shell sort (Pratt, 1971)|Shell sort (Pratt, 1971, Knuth, 1973)|Shell sort (Incerpi & Sedgewick, 1985, Knuth)|Shell sort (Sedgewick, 1982)|Shell sort (Sedgewick, 1986)|Shell sort (Gonnet & Baeza-Yates, 1991)|Shell sort (Tokuda, 1992)|Shell sort (Ciura, 2001, Dovgopol, 2011)
---|---|---|---|---|---|---|---|---|---|---|---|---|---
20|0|0|0|0|0|0|0|0|0|0|0|0|0
40|0|0|0|0|0|0|0|0|0|0|0|0|0
80|0|0|0|0|0|0|0|0|0|0|0|0|0
160|0|0|1|0|0|0|0|0|0|0|0|0|0
320|0|0|0|0|0|0|0|0|0|0|0|0|0
640|0|0|0|0|0|0|0|0|0|0|0|0|0
1280|0|0|0|0|0|0|0|1|0|0|0|0|0
2560|2|0|0|0|0|1|0|0|0|0|0|0|1
5120|11|2|0|0|1|2|1|2|1|1|0|1|1
10240|45|3|2|2|2|7|1|2|1|3|1|2|1
20480|291|21|9|9|8|26|8|8|6|6|5|5|4
40960|768|64|14|14|17|47|15|13|11|12|11|12|10
81920|2434|571|29|31|30|87|27|26|24|27|24|26|24
163840|8019|2065|63|67|66|196|58|53|51|55|52|56|52
327680|21910|4709|132|140|135|441|117|115|108|117|108|111|110

# Случайный массив

Записей|Insert sort|Shell sort (Shell, 1959)|Shell sort (Frank & Lazarus, 1960)|Shell sort (Hibbard, 1963)|Shell sort (Papernov & Stasevich, 1965)|Shell sort (Pratt, 1971)|Shell sort (Pratt, 1971, Knuth, 1973)|Shell sort (Incerpi & Sedgewick, 1985, Knuth)|Shell sort (Sedgewick, 1982)|Shell sort (Sedgewick, 1986)|Shell sort (Gonnet & Baeza-Yates, 1991)|Shell sort (Tokuda, 1992)|Shell sort (Ciura, 2001, Dovgopol, 2011)
---|---|---|---|---|---|---|---|---|---|---|---|---|---
20|0|0|0|0|0|0|0|0|0|0|0|0|0
40|0|0|0|0|0|0|0|0|0|0|0|0|0
80|0|0|0|0|0|0|0|0|0|0|0|0|0
160|0|0|0|0|0|0|0|0|0|0|0|0|0
320|0|0|0|0|0|0|0|0|0|0|0|0|0
640|0|0|0|0|1|0|0|0|0|0|0|0|0
1280|2|0|0|0|0|0|0|0|0|0|0|0|0
2560|12|0|0|0|0|0|0|0|0|0|0|0|0
5120|48|1|0|2|1|2|1|1|0|0|0|0|0
10240|242|4|2|3|3|7|2|2|2|2|3|2|2
20480|784|10|7|7|8|17|7|6|6|8|6|7|6
40960|3483|38|16|16|16|46|20|18|15|16|16|17|16
81920|12221|98|38|39|40|91|34|29|29|30|28|31|30
163840|49441|322|82|87|92|209|76|62|60|66|63|63|79
327680|196325|704|192|198|196|457|176|136|131|138|129|131|224

# Выводы

Оба алгоритма хорошо работают на почти отсортированном массиве. Особенно хорошо на нем работает InsertSort, т.к. он делает меньше проходов.

На частично или вовсе неотсортированных массивах Insert Sort ведет себя не очень хорошо.

Касаемо Shell Sort.

Последовательность из оригинльой работы (Shell, 1959) показывает себя не лучшим образом из-за того что идея "половинного деления" видимо не слишком хороша, хотя и лучще чем Insert Sort. Проблема, видимо, в том что при таком подходе у нас данные делятся на блоки которые сольются только в самом конце, тогда как при других подходах данные попадают в разные группы и сортируются с разными данными пока массив сортируемых данных еще сравнитенльно небольшой.

Поясню свою мысль. Например вот так элементы сортируются в Shell, 1959

Элемент|4 сортировка|2 сортировка
---|---|---
1|**1 группа**|**1 группа**
2|2 группа|2 группа
3|3 группа|**1 группа**
4|4 группа|2 группа
5|**1 группа**|**1 группа**
6|2 группа|2 группа
7|3 группа|**1 группа**
8|4 группа|2 группа
9|**1 группа**|**1 группа**

Видна тенденция что они сортруются сами с теми-же что и раньше (с добавлением новых), а вот пример для Papernov & Stasevich, 1965 последовательности

Элемент|5 сортировка|3 сортировка
---|---|---
1|**1 группа**|**1 группа**
2|2 группа|2 группа
3|3 группа|3 группа
4|4 группа|**1 группа**
5|5 группа|2 группа
6|**1 группа**|3 группа
7|2 группа|**1 группа**
8|3 группа|2 группа
9|4 группа|3 группа

Группы перемешаны значительно лучше. По видимому, существенное падение производительности на 10% массиве объясняется именно этой причиной.

Последовательность Pratt, 1971, по видимому делает слишком много небольших ходов и в результате слишком много сортировок, в результате она получается не слишком хороша.

Последовательность Ciura, 2001 (с добавлением Dovgopol, 2011) хороша, но она, в отличии от остальных, выведена экспериментально и не имеет формулы, а потому имеет слишком мало шагов как только экспериментально рассчитанных шагов начинает нехватать она начинает проигрывать (хотя в своей области она и хороша).

Про остальные последовательности сказать особо нечего, все они выдают результат коррелирующий со сложностью в худшем случае. Последовательности одной сложности выдают сопоставимые результаты.