# Генератор G-кода для 3D-печати
Эта программа позволяет сгенерировать G-код для 3D-принтера, используя код на C++. G-код используется для команд принтеру относительно перемещения и экструзии пластика для создания желаемого объекта.

## Возможности
- Поддержка нескольких экструдеров
- Управление температурой сопел и подогрева стола
- Функция очистки экструдера
- Функции перемещения для абсолютного и относительного позиционирования
- Управление слоями
- Различные функции печати, включая линии, дуги и формы
## Начало работы

Для использования генератора G-кода выполните следующие шаги:

1. **Клонирование репозитория:**

   ```
   git clone https://github.com/Onishenko-sci/G-Code-From-math
   ```

2. **Адаптация кода в `main.cpp:`**

   Отредактируйте файл `main.cpp` в соответствии с вашими потребностями, добавьте или измените функциональность.

3. **Сборка проекта и g-code файла:**
   
   Используйте `make` для сборки проекта и g-code.
   ```
   make
   ```
   Программа выполнит генерацию G-кода на основе обновленного кода в main.cpp и сохранит его в директорию проекта.


# Основные функции

#### Конструктор `gcode(std::string file_name)`

Инициализирует объект `gcode` и открывает файл для записи G-кода.

##### Параметры

- `file_name`: Имя файла для записи G-кода.


## Управление экструдером

##### `void set_extruder(unsigned int extr_number)`

Устанавливает активный экструдер.

##### `void set_temperature(unsigned int temperature, unsigned int extr, bool and_wait = false)`

Устанавливает температуру сопла экструдера.

- `temperature`: Требуемая температура.
- `extr`: Номер экструдера.
- `and_wait`: Флаг, указывающий, ждать ли достижения температуры (по умолчанию `false`).

##### `void set_bed_temperature(unsigned int temperature, bool and_wait = false)`

Устанавливает температуру подогрева стола.

- `temperature`: Требуемая температура подогрева.
- `and_wait`: Флаг, указывающий, ждать ли достижения температуры (по умолчанию `false`).

##### `void clean_extruder(unsigned int extr_number)`

Запускает процедуру очистки указанного экструдера.

##### `void extrusion(double how_much)`

Управляет экструзией (выдвижением) пластика. Используется для откатов.

- `how_much`: Количество выдвигаемого пластика.

## Управление движением

##### `void move_to_origin()`

Перемещает печатающую головку в начальное положение (нулевые координаты).

##### `void abs_move(Vector2D where, int spd = 3600)`

Перемещает печатающую головку в указанное абсолютное положение с заданной скоростью.

- `where`: Координаты назначения.
- `spd`: Скорость перемещения (по умолчанию `3600`).

##### `void abs_move(double x, double y, int spd = 3600)`

Перемещает печатающую головку в указанное абсолютное положение по осям X и Y с заданной скоростью.

- `x`, `y`: Координаты назначения.
- `spd`: Скорость перемещения (по умолчанию `3600`).

##### `void abs_move(double x, double y, double z, int spd = 3600)`

Перемещает печатающую головку в указанное абсолютное положение по осям X, Y и Z с заданной скоростью.

- `x`, `y`, `z`: Координаты назначения.
- `spd`: Скорость перемещения (по умолчанию `3600`).

##### `void rel_move(Vector2D where, int spd = 3600)`

Перемещает печатающую головку на указанное относительное расстояние с заданной скоростью.

- `where`: Вектор относительного перемещения.
- `spd`: Скорость перемещения (по умолчанию `3600`).

##### `void rel_move(double x, double y, int spd = 3600)`

Перемещает печатающую головку на указанное относительное расстояние по осям X и Y с заданной скоростью.

- `x`, `y`: Расстояние относительного перемещения.
- `spd`: Скорость перемещения (по умолчанию `3600`).

##### `void next_layer(double layer_height)`

Переходит на следующий слой поднимая экструдер на заданную высоту.

- `layer_height`: Высота слоя.

## Функции печати

##### `void line(Vector2D where, int spd = 0)`

Печатает линию от текущей позиции до указанных координат с заданной скоростью.

- `where`: Координаты конечной точки линии.
- `spd`: Скорость печати (по умолчанию `0`).

##### `void line(double x, double y, int spd = 0)`

Печатает линию от текущей позиции до указанных координат по осям X и Y с заданной скоростью.

- `x`, `y`: Координаты конечной точки линии.
- `spd`: Скорость печати (по умолчанию `0`).

##### `void abs_line(double x, double y, int spd = 0)`

Печатает абсолютную линию от текущей позиции до указанных координат по осям X и Y с заданной скоростью.

- `x`, `y`: Абсолютные координаты конечной точки линии.
- `spd`: Скорость печати (по умолчанию `0`).

##### `void arc(double radius, double angle, double arc_angle = 90.0, int spd = 0)`

Печатает дугу с указанным радиусом, углом и скоростью.

- `radius`: Радиус дуги.
- `angle`: Угол начальной точки дуги.
- `arc_angle`: Угловой размер дуги (по умолчанию `90.0`).
- `spd`: Скорость печати (по умолчанию `0`).

---

