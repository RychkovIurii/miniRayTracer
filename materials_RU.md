# Материалы и их свойства

## Структура материала

```c
typedef struct	s_material
{
    t_tuple		color;             // Основной цвет материала
    double		ambient;           // Фоновое освещение (0.0 - 1.0)
    double		diffuse;           // Рассеянное освещение (0.0 - 1.0)
    double		specular;          // Зеркальное отражение (0.0 - 1.0)
    double		shininess;         // Гладкость блика (чем больше, тем уже и ярче блик)
    t_pattern	pattern;           // Узор (если есть)
    int			has_pattern;       // Флаг: есть ли узор (1 - да, 0 - нет)
    double		reflective;        // Отражение (0.0 - 1.0, 1.0 - зеркало)
    double		transparency;      // Прозрачность (0.0 - 1.0)
    double		refractive_index;  // Коэффициент преломления (1.0 - воздух, 1.5 - стекло, 2.4 - алмаз)
}			t_material;
```

## Оптимальные значения для разных материалов

| Материал         | ambient | diffuse | specular | shininess | reflective | transparency | refractive_index |
|------------------|---------|---------|----------|-----------|------------|--------------|------------------|
| Пластик          | 0.1-0.2 | 0.7-0.9 | 0.2-0.4  | 50-100    | 0.1-0.2    | 0.0          | 1.0              |
| Металл           | 0.2-0.3 | 0.3-0.6 | 0.7-1.0  | 100-500   | 0.7-1.0    | 0.0          | 1.0              |
| Стекло           | 0.1-0.2 | 0.1-0.3 | 0.9-1.0  | 200-500   | 0.0-0.1    | 0.9-1.0      | 1.5              |
| Вода             | 0.1     | 0.1-0.3 | 0.3-0.6  | 100-200   | 0.0        | 1.0          | 1.33             |
| Керамика         | 0.2     | 0.8     | 0.3      | 100       | 0.1-0.2    | 0.0          | 1.0              |
| Алмаз            | 0.1     | 0.1     | 1.0      | 300-500   | 0.1-0.3    | 1.0          | 2.42             |
| Матовое стекло   | 0.1     | 0.3-0.5 | 0.3-0.5  | 50-150    | 0.0-0.1    | 0.8-1.0      | 1.5              |
| Зеркало          | 0.0     | 0.1     | 1.0      | 250-500   | 1.0        | 0.0          | 1.0              |

## Примеры кода для разных материалов

### Матовый пластик (сфера)

```c
sphere->material = (t_material){
    .color = create_color(1.0, 0.0, 0.0),  // Красный
    .ambient = 0.1,
    .diffuse = 0.9,
    .specular = 0.3,
    .shininess = 50,
    .reflective = 0.1,
    .transparency = 0.0,
    .refractive_index = 1.0
};
```

### Отполированный металл (золотой шар)

```c
sphere->material = (t_material){
    .color = create_color(1.0, 0.8, 0.0),  // Золотистый
    .ambient = 0.2,
    .diffuse = 0.3,
    .specular = 1.0,
    .shininess = 300,
    .reflective = 0.9,
    .transparency = 0.0,
    .refractive_index = 1.0
};
```

### Стеклянная сфера

```c
sphere->material = (t_material){
    .color = create_color(1.0, 1.0, 1.0),  // Прозрачный
    .ambient = 0.1,
    .diffuse = 0.1,
    .specular = 1.0,
    .shininess = 500,
    .reflective = 0.1,
    .transparency = 1.0,
    .refractive_index = 1.5  // Стекло
};
```

### Зеркало

```c
mirror->material = (t_material){
    .color = create_color(1.0, 1.0, 1.0),  // Белый (основной цвет не важен)
    .ambient = 0.0,
    .diffuse = 0.1,
    .specular = 1.0,
    .shininess = 400,
    .reflective = 1.0,
    .transparency = 0.0,
    .refractive_index = 1.0
};
```

## Примечания

- `diffuse` отвечает за рассеянное освещение, оптимальное значение зависит от материала.
- Если объект матовый → `diffuse` высокий (0.8 - 0.9).
- Если объект гладкий → `diffuse` низкий (0.2 - 0.5).
- Если объект прозрачный → `diffuse` низкий, а `transparency` высокий.
- Зеркала и металлы больше используют `specular`, чем `diffuse`.
