# SOLID Принципи в Java

SOLID е акроним за пет основни принципа на обектно-ориентираното програмиране, които помагат за създаването на по-разбираем, поддържан и разширяем код. Те са особено полезни при работа по големи софтуерни проекти.

---

## 1. **S**ingle Responsibility Principle (Принцип на единствената отговорност)

### Описание:
Класът трябва да има само една причина за промяна. Това означава, че той трябва да отговаря за една конкретна задача или функционалност.

### Пример:

```java
// Лош пример
class Report {
    public void generateReport() {
        // Логика за генериране на отчет
    }

    public void saveToFile(String filename) {
        // Логика за записване на отчета във файл
    }
}

// Добър пример
class Report {
    public void generateReport() {
        // Логика за генериране на отчет
    }
}

class ReportSaver {
    public void saveToFile(String filename, Report report) {
        // Логика за записване на отчета във файл
    }
}
```

### Обяснение:
В лошия пример, класът `Report` е отговорен както за генерирането, така и за записването на отчета. В добрия пример задачите са разделени в два отделни класа.

---

## 2. **O**pen/Closed Principle (Принцип на отвореност/затвореност)

### Описание:
Класовете трябва да са отворени за разширяване, но затворени за модификация. Това означава, че трябва да можете да добавяте нова функционалност, без да променяте съществуващия код.

### Пример:

```java
// Лош пример
class Shape {
    public String type;
}

class AreaCalculator {
    public double calculateArea(Shape shape) {
        if (shape.type.equals("circle")) {
            // Логика за кръг
        } else if (shape.type.equals("rectangle")) {
            // Логика за правоъгълник
        }
        return 0;
    }
}

// Добър пример
interface Shape {
    double calculateArea();
}

class Circle implements Shape {
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }

    public double calculateArea() {
        return Math.PI * radius * radius;
    }
}

class Rectangle implements Shape {
    private double width, height;

    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    public double calculateArea() {
        return width * height;
    }
}
```

### Обяснение:
В добрия пример нови форми могат да бъдат добавяни, без да се променя съществуващият код.

---

## 3. **L**iskov Substitution Principle (Принцип на заместване на Лисков)

### Описание:
Обектите на подкласовете трябва да могат да заменят обектите на базовия клас, без да нарушават функционалността на програмата.

### Пример:

```java
// Лош пример
class Bird {
    public void fly() {
        System.out.println("Flying...");
    }
}

class Ostrich extends Bird {
    @Override
    public void fly() {
        throw new UnsupportedOperationException("Ostriches can't fly!");
    }
}

// Добър пример
interface Bird {
    void eat();
}

interface FlyingBird extends Bird {
    void fly();
}

class Sparrow implements FlyingBird {
    public void eat() {
        System.out.println("Eating...");
    }

    public void fly() {
        System.out.println("Flying...");
    }
}

class Ostrich implements Bird {
    public void eat() {
        System.out.println("Eating...");
    }
}
```

### Обяснение:
В добрия пример, неспособността на щрауса да лети не нарушава принципа, тъй като класовете са разделени според функционалността.

---

## 4. **I**nterface Segregation Principle (Принцип на сегрегация на интерфейса)

### Описание:
Клиентите не трябва да бъдат принуждавани да имплементират интерфейси, които не използват.

### Пример:

```java
// Лош пример
interface Animal {
    void eat();
    void fly();
}

class Dog implements Animal {
    public void eat() {
        System.out.println("Eating...");
    }

    public void fly() {
        throw new UnsupportedOperationException("Dogs can't fly!");
    }
}

// Добър пример
interface EatingAnimal {
    void eat();
}

interface FlyingAnimal {
    void fly();
}

class Dog implements EatingAnimal {
    public void eat() {
        System.out.println("Eating...");
    }
}
```

### Обяснение:
В добрия пример интерфейсите са разделени, така че класовете имплементират само необходимата функционалност.

---

## 5. **D**ependency Inversion Principle (Принцип на инверсия на зависимостите)

### Описание:
Модулите с висока степен на абстракция не трябва да зависят от модули с ниска степен на абстракция. И двата трябва да зависят от абстракции. Абстракциите не трябва да зависят от детайли; детайлите трябва да зависят от абстракции.

### Пример:

```java
// Лош пример
class MySQLDatabase {
    public void connect() {
        System.out.println("Connected to MySQL database.");
    }
}

class Application {
    private MySQLDatabase database;

    public Application() {
        database = new MySQLDatabase();
    }

    public void start() {
        database.connect();
    }
}

// Добър пример
interface Database {
    void connect();
}

class MySQLDatabase implements Database {
    public void connect() {
        System.out.println("Connected to MySQL database.");
    }
}

class Application {
    private Database database;

    public Application(Database database) {
        this.database = database;
    }

    public void start() {
        database.connect();
    }
}
```

### Обяснение:
В добрия пример приложението зависи от интерфейса `Database`, а не от конкретната имплементация, което позволява лесна смяна на базата данни.

---

Спазването на тези принципи ще направи вашия код по-чист, по-разбираем и лесен за поддръжка.
