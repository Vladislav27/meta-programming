Задание 1.  
Есть два класса, А и В.  
У каждого из них есть свой публичный интерфейс.  
Нужно написать новый шаблонный класс С, который в зависимости от шаблонного параметра будет выполнять разные роли.  
1. Прокси  
Обращение объектов класса А к объектам класса В должно выполняться не напрямую, а через аналогичный интерфейс класса-прокси.  
2. Медиатор  
Класс С должен иметь возможность хранить целый набор объектов класса В(или указателей на них) и в случае обращения от объекта класса А автоматически выбирать объект класса В и передавать ему запрос.  
3. Наблюдатель  
Должна появиться возможность для объектов класса А подписываться на объекты класса В. Тогда при обновлении объекта класса В объект С должен уведомлять всех подписчиков этого объекта-объекты класса А.  
