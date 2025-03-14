# Minesweeper-Project
End-Term Project for the course Introduction to Programming

Целта на играта е да се разкрият вскичи позиции в дадена квадратна матрица, които не са мини.

Играчът печели, ако правилно отбележи позициите на всички мини и отвори всички квадратчета, и съответно губи, ако разкрие поне една мина.

При започване на играта потребителят избира с каква размерност ( N ) да е полето ( между 3 и 10 ). Ако размерността не е в този диапазон, потребителят ще бъде помолен да въведе нова стойност. Освен размерността, потребителят трябва да въведе брой мини ( между 1 и 3 * N ), ако и те не са в допустимия диапазон, ще трябва да бъдат въведени стойности отново. 

В конзолата се изпълняват следните команди:

• OPEN 
  - отваря кутийката, ако не е мина и около нея няма празни кутийки
  - отваря кутийката и съседните кутийки около нея ако те са празни
  - ако вече е отворена, ще се изведе съобщение, че кутийката не може да се отвори повторно
  - ако е поставен флаг върху кутийката, тя не може да се отвори
  
• FLAG
  - маркира квадратчето като "мина". Ако всички мини са маркирани и всички други квадратчета са отворени, играта приключва с успех.
  
• UNFLAG
  - отмаркира квадрачето като "мина". Ако квадратчето не е било маркирано, то се извежда подходящо съобщение за грешка.
  
  
