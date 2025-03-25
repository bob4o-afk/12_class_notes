// Задача 1: Преобразуване на масив от имена
// Описание:
// Даден е масив от обекти с имена и възрасти. Преработете, за да получите масив само с имената.
function getNames(arr) {
    return arr.map(element => element.name);
}

// Задача 2: Филтриране на четни числа
// Описание:
// Даден е масив от числа. Върнете нов масив, който съдържа само четните числа.
function getEvenNumbers(arr) {
    return arr.filter(num => num % 2 === 0);
}

// Задача 3: Удвояване на числата в масив
// Описание:
// Даден е масив от числа. Върнете нов  нов масив, в който всички числа са удвоени.
function doubleNumbers(arr) {
    return arr.map(num => num * 2);
}
// Задача 4: Намерете първото число по-голямо от 20
// Описание:
// Даден е масив от числа. Намерете първото число, което е по-голямо от 20.
function getNumber(arr) {
    return arr.find(element => element > 20);
}

// Задача 5: Групиране на хора по възраст
// Описание:
// Даден е масив от обекти, съдържащи име и възраст на хора. Използвайте reduce(), за да групирате хората по възраст.
function groupByAge(arr) {
    return arr.reduce((acc, element) => {
        if (!acc[element.age]) {
            acc[element.age] = [];
        }
        acc[element.age].push(element.name);
        return acc;
    }, {});
}

// Задача 6: Уникални стойности
// Описание:
// Даден е масив от числа с дублиращи се стойности. Върнете масив само с уникални стойности.

function getUniqueValues(arr) {
    let s = new Set();
    arr.forEach( e => s.add(e) );
    return s;
}

// Задача 7: Обръщане на ключове и стойности в обект
// Описание:
// Даден е обект с ключове и стойности. Използвайте Object.entries() и reduce(), за да създадете нов обект, в който ключовете и стойностите са разменени.

function reverseKeysAndValues(obj) {
    return Object.entries(obj).reduce((acc, [key, value]) => {
        acc[value] = key;
        return acc;
    }, {});
}

// Задача 8: Честота на срещане на елементи в масив
// Описание:
// Даден е масив с повтарящи се стойности. Използвайте reduce(), за да създадете обект, който съдържа броя на срещанията на всяка стойност.
function countOccurrences(arr) {
    return arr.reduce((acc, element) => {
        if (!acc[element]) {
            acc[element] = 0;
        }
        acc[element]++;
        return acc;
    }, {});
}


const namesArray = [{ name: 'John', age: 21 }, { name: 'Mike', age: 20 }, { name: 'Smith', age: 40 }];
const numbersArray = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const doubleNumbersArray = [1, 2, 3, 4];
const findNumberArray = [1, 2, 30, 22, 1];
const groupByAgeArray = [{ name: "John", age: 21 },{ name: "Mike", age: 20 },{ name: "Smith", age: 20 }];
const uniqueValuesArray = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2];
const reverseKeysAndValuesArray = { name: 'John', age: 21 };
const countOccurrencesArray = [1, 2, 1, 2, 3, 2, 4, 3, 2, 1, 1, 2];

console.log(
    "1: ", getNames(namesArray), 
    "\n2: ", getEvenNumbers(numbersArray), 
    "\n3: ", doubleNumbers(doubleNumbersArray), 
    "\n4: ", getNumber(findNumberArray), 
    "\n5: ", groupByAge(groupByAgeArray),  
    "\n6: ", getUniqueValues(uniqueValuesArray), 
    "\n7: ", reverseKeysAndValues(reverseKeysAndValuesArray),
    "\n8: ", countOccurrences(countOccurrencesArray)
);