ray trasing - под процес на rendering - тресират се лъчи за да се намерят точките

3d обекти моделиране - видове модели

polygonal model - повърхността се разделя на полигони, а те на триъгълник и се дефинират с т.н нормали


минава през 4 пространства
- local space - 3d object modeling
- global space - текстури и камери 
- camera space - изрязват се моделите които не се виждат
- screen space - растеризация на цялата повърхност на тялото, z-buffer алгоритъм и се стартира shading-a

rendering pipeline


шейдингът е 2 основни типа - ray tracing и radiosity 

backward ray tracing - концепция 

ray tracing tree - как се изчислява лъч стигащ до камерата - от transmited и reflecterd и прочие (презентацията)

създава се лъчево дърво (ray tracing tree) - показва се същноста на алгоритъма - спира се на няква дълбочина - бавен алгоритъм 

има два казуса:
- намиране на пресечна точка между лъч и обект
- намиране на посоката и интензитета на отразения лъч 