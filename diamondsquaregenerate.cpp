#include "diamondsquaregenerate.h"
#include <algorithm>

DiamondSquareGenerate::DiamondSquareGenerate(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_rng.seed(m_seed);
}


void DiamondSquareGenerate::setRoughness(double v)
{
    if (m_roughness == v) return;

    m_roughness = v;
    emit roughnessChanged();
    m_chunks.clear();
    m_cache.clear();
    updateChanks();
    update();


}

void DiamondSquareGenerate::setWaterLevel(double v)
{
    if (m_waterLevel == v) return;
    m_waterLevel = v;
    emit waterLevelChanged();
    m_chunks.clear();
    m_cache.clear();
    updateChanks();
    update();
}


void DiamondSquareGenerate::setSeed(quint32 s)
{
    if (m_seed == s) return;

    m_seed = s;
    emit seedChanged();
    m_cache.clear();
    m_chunks.clear();
    updateChanks();
    update();
}

void DiamondSquareGenerate::setCamX(double x)
{
    if (m_camX == x) return;
    m_camX = x;
    emit camChanged();
    updateChanks();
    update();
}

void DiamondSquareGenerate::setCamY(double y)
{
    if (m_camY == y) return;
    m_camY = y;
    emit camChanged();
    updateChanks();
    update();
}

void DiamondSquareGenerate::setCamScale(double v)
{
    if (m_camScale == v) return;
    m_camScale = v;
    emit camChanged();
    updateChanks();
    update();
}


Chunk DiamondSquareGenerate::generateChunk(int cx, int cy)
{
    Chunk chunk;
    chunk.cx = cx;
    chunk.cy = cy;

    const int N = m_chunkSize;
    const int step = N - 1;
    chunk.heightMap.assign(N, QVector<double>(N, 0.0));

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
        {
            int wx = cx * step + x;
            int wy = cy * step + y;
           chunk.heightMap[y][x] = getHeight(wx, wy);
        }

    chunk.generated = true;
    return chunk;
}


void DiamondSquareGenerate::updateChanks()
{
    double worldX = (width() * 0.5 - m_camX) / m_camScale;
    double worldY = (height() * 0.5 - m_camY) / m_camScale;

    int ccx = std::floor(worldX / (m_chunkSize - 1));
    int ccy = std::floor(worldY / (m_chunkSize - 1));

    for (int y = ccy - m_viewRadius; y <= ccy + m_viewRadius; y++){
        for (int x = ccx - m_viewRadius; x <= ccx + m_viewRadius; x++){

            QPoint key(x, y);

            if (!m_chunks.contains(key))
                m_chunks[key] = generateChunk(x, y);
        }
    }

    update();
}

double DiamondSquareGenerate::randomRange(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(m_rng);
}



double DiamondSquareGenerate::hash(int x, int y) const
{
    uint32_t n = x * 73856093u ^ y * 19349663u ^ m_seed;
    n = (n << 13) ^ n;
    return 1.0 - ((n * (n * n * 15731u + 789221u) + 1376312589u)
                  & 0x7fffffff) / 1073741824.0;
}


// Находим наименьший бит который ненулевой хотя бы у одной координаты
// Он и есть размер блока для этой точки
int DiamondSquareGenerate::blockSize(int x, int y)
{
    int base = 1;
    while (((x & base) == 0) && ((y & base) == 0))
        base <<= 1;
    return base;
}

// Если оба бита выставлены — это square step (центр квадрата)
// Если только один — это diamond step (середина ребра)

bool DiamondSquareGenerate::isSquare(int x, int y, int base)
{
     return ((x & base) != 0) && ((y & base) != 0);
}

double DiamondSquareGenerate::cornerValue(int worldX, int worldY)
{
    uint32_t n = (uint32_t)(worldX * 73856093u) ^ (uint32_t)(worldY * 19349663u) ^ m_seed;
    n = (n << 13) ^ n;
    double v = 1.0 - ((n * (n * n * 15731u + 789221u) + 1376312589u)
                      & 0x7fffffff) / 1073741824.0;
    return v * m_offset;
}

QColor DiamondSquareGenerate::heightToColor(double t)
{
    // Уровни: глубокая вода / вода / песок / трава / горы / снег
    struct Stop { double t; QColor color; };
    static const Stop stops[] = {
        { 0.00, QColor(  0,  20,  80) },  // глубокая вода
        { 0.35, QColor( 30,  80, 200) },  // вода
        { 0.42, QColor(210, 190, 140) },  // песок
        { 0.55, QColor( 60, 140,  40) },  // трава
        { 0.75, QColor(100,  80,  60) },  // горы
        { 0.90, QColor(160, 160, 160) },  // скалы
        { 1.00, QColor(240, 240, 255) },  // снег
    };
    constexpr int N = sizeof(stops) / sizeof(stops[0]);

    // Линейная интерполяция между ближайшими стопами
    for (int i = 1; i < N; i++) {
        if (t <= stops[i].t) {
            double f = (t - stops[i-1].t) / (stops[i].t - stops[i-1].t);
            int r = stops[i-1].color.red()   + f * (stops[i].color.red()   - stops[i-1].color.red());
            int g = stops[i-1].color.green() + f * (stops[i].color.green() - stops[i-1].color.green());
            int b = stops[i-1].color.blue()  + f * (stops[i].color.blue()  - stops[i-1].color.blue());
            return QColor(r, g, b);
        }
    }
    return stops[N-1].color;
}

double DiamondSquareGenerate::getHeight(int x, int y)
{
    // За границей карты — 0 (или можно сделать тороидально)
    if (x < 0 || y < 0 || x > m_worldSize || y > m_worldSize)
        return 0.0;

    // Угловые точки карты — детерминированы
    if ((x == 0 || x == m_worldSize) && (y == 0 || y == m_worldSize))
        return randForPoint(x, y) * m_offset;

    // Уже посчитано — берём из кэша
    QPoint key(x, y);
    auto it = m_cache.find(key);
    if (it != m_cache.end())
        return it.value();

    // Определяем размер блока и тип шага
    int base = 1;
    while (((x & base) == 0) && ((y & base) == 0))
        base <<= 1;

    double value;
    double scale = m_offset * (double)base / m_worldSize * m_roughness;

    if (((x & base) != 0) && ((y & base) != 0))
    {
        // Square step — центр квадрата, усредняем 4 угла
        double avg = (getHeight(x - base, y - base)
                      + getHeight(x + base, y - base)
                      + getHeight(x - base, y + base)
                      + getHeight(x + base, y + base)) * 0.25;
        value = avg + randForPoint(x, y) * scale;
    }
    else
    {
        // Diamond step — середина ребра, усредняем 4 соседа
        double avg = (getHeight(x - base, y)
                      + getHeight(x + base, y)
                      + getHeight(x,        y - base)
                      + getHeight(x,        y + base)) * 0.25;
        value = avg + randForPoint(x, y) * scale;
    }

    m_cache[key] = value;
    return value;
}

double DiamondSquareGenerate::randForPoint(int x, int y)
{
    // Хэш координат + seed → псевдослучайное число [-1..1]
    uint32_t n = (uint32_t)(x * 73856093u) ^ (uint32_t)(y * 19349663u) ^ m_seed;
    n = (n << 13) ^ n;
    n = n * (n * n * 15731u + 789221u) + 1376312589u;
    return (double)(n & 0x7fffffff) / 1073741824.0 - 1.0;  // [-1..1]
}
void DiamondSquareGenerate::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing, false);

    const int cs = m_chunkSize;
    const int step = cs - 1;

    double worldCenterX = (width()  * 0.5 - m_camX) / m_camScale;
    double worldCenterY = (height() * 0.5 - m_camY) / m_camScale;

    for (auto it = m_chunks.cbegin(); it != m_chunks.cend(); ++it)
    {
        const Chunk &chunk = it.value();

        for (int y = 0; y < cs - 1; y++)
            for (int x = 0; x < cs - 1; x++)
            {
                // Среднее четырёх углов ячейки
                double h = (chunk.heightMap[y][x]
                            + chunk.heightMap[y][x+1]
                            + chunk.heightMap[y+1][x]
                            + chunk.heightMap[y+1][x+1]) * 0.25;

                double t = std::clamp(h / m_offset * 0.5 + 0.5, 0.0, 1.0);
                t = std::clamp(t - m_waterLevel + 0.42, 0.0, 1.0);

                double worldX = chunk.cx * step + x;
                double worldY = chunk.cy * step + y;

                double sx = (worldX - worldCenterX) * m_camScale + width()  * 0.5;
                double sy = (worldY - worldCenterY) * m_camScale + height() * 0.5;

                double cellSize = m_camScale + 1.0;

                painter->fillRect(QRectF(sx, sy, cellSize, cellSize),
                                  heightToColor(t));
            }
    }
}

void DiamondSquareGenerate::componentComplete()
{
    QQuickPaintedItem::componentComplete();


}

