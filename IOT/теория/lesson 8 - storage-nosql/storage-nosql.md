NOSQL

Значение: not only sql

То е:
- schema-less, multi-model
- structured, semi-structured, unstructured
- distributed, horizontally scalable

nosql db типове:
- key-value stores - то е string

Имаме:
key -> value

Много е бързо и много лесно за използване


pros:
- може да handle-ва много данни
- много бързо
- много лесно за използване

cons:
- не може да се правят сложни заявки
- липса на възможност за сканиране

use case:
- session data
- преференции на потребител
- live дата (от сензори примерно, chart примерно)


Друг тип на nosql db е: document databases
- разширение на key-value stores
- може да правим query-та върху стойностите и върху ключовете
- групират се в колекции

pros:
- много лесно за използване
- много flexible
- по-бързо от релационните бази данни

cons:
- query-тата са лимитирани до key и indexes
- без релации

- use case:
- profile data
- sensor data

Друг тип на nosql db е: graph databases
- съхраняват данните като граф
- много лесно за намиране на данни

pros:
- много бързо за намиране на данни
- резултати в реално време
- flexible структура

основа за digital twins
cons:
- не е подходящ за много данни

Друг тип на nosql db е: column-family databases
- съхраняват данните като колекция от колони, групирани в семейства

*CF - column family, R - row

pros:
- flexible
- скалируем

cons:
- no relation support

use case:
- time series data
- log data
- дата, която трябва да се съхранява за дълго време





SQL VS NoSQL

SQL:
- таблици
- constraints
- релации

NoSQL:
- key value
- таблици
- документи
- графове


======
SQL:
- вертикално скалиране

NoSQL:
- хоризонтално скалиране

======
SQL:
- лесно скалиране вертикално
- трудно скалиране за хоризонтално

NoSQL:
- лесно скалиране хоризонтално
- лесно скалиране вертикално (повече nodes)

======
SQL:
- SQL заявки

NoSQL:
- REST API
- CRUD - create, read, update, delete

======
SQL:
- ползваме когато не знаем access pattern-а (гъвсавост при искарване на данни)
- когато искаме типизация

NoSQL:
- ползваме когато знаем access pattern-а
- когато искаме бързина
- когато искаме гъвкавост

Когато data модела прилича на някаква бази данни, тогава се ползва нея.


ACID VS BASE

ACID:
    - atomicity (неделимост, че транзакцията ще се изпълни - от и двете страни ще се изпълни), 
    - consistency (имаме constrains, които лимитират заявките), 
    - isolation (имаме последователност, върху едни и същи данни се изпъляват последователно заявките), 
    - durability (ако се случи нещо може да се rollback-не):
- RDBMS
- транзакции

BASE:
    - basically available (винаги да има отговор)
    - soft state (състоянието може да се промени)
    - eventually consistent (всички данни ще се синхронизират)

- ползва се за NoSQL предимно

CAP theorem:
- consistency - всички данни са еднакви (еднакъв отговор), дори и след промяна
- availability - всеки заявка ще получи отговор
- partitioning - разделяне на данните