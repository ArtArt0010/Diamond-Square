#include "diamondsquaregenerate.h"
#include <algorithm>

DiamondSquareGenerate::DiamondSquareGenerate(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{

}


void DiamondSquareGenerate::setRoughness(double v)
{
    if (m_roughness == v) return;

    m_roughness = v;
    emit roughnessChanged();
    m_chunks.clear();
    updateChanks();
    update();


}

void DiamondSquareGenerate::setWaterLevel(double v)
{
    if (m_waterLevel == v) return;
    m_waterLevel = v;
    emit waterLevelChanged();
    m_chunks.clear();
    updateChanks();
    update();
}


void DiamondSquareGenerate::setSeed(quint32 s)
{
    if (m_seed == s) return;

    m_seed = s;
    emit seedChanged();
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

   std::mt19937 rng(m_seed ^ (uint32_t)(cx * 1234567u) ^ (uint32_t)(cy * 7654321u));
    // Углы
    chunk.heightMap[0][0] = cornerValue(cx * step, cy * step);
    chunk.heightMap[0][N-1] = cornerValue((cx+1) * step, cy * step);
    chunk.heightMap[N-1][0] = cornerValue(cx * step, (cy+1) * step);
    chunk.heightMap[N-1][N-1] = cornerValue((cx+1) * step, (cy+1) * step);

    // Загружаем целые края от готовых соседей
    bool topEx  = m_chunks.contains(QPoint(cx, cy-1));
    bool bottomEx = m_chunks.contains(QPoint(cx, cy+1));
    bool leftEx = m_chunks.contains(QPoint(cx-1, cy));
    bool rightEx = m_chunks.contains(QPoint(cx+1, cy));


    // Если сосед уже существует — копируем его край целиком
    if (topEx){
        for (int x = 0; x < N; x++){
            chunk.heightMap[0][x] = m_chunks[QPoint(cx, cy-1)].heightMap[N-1][x];
        }
    }

    if (bottomEx){
        for (int x = 0; x < N; x++){
            chunk.heightMap[N-1][x] = m_chunks[QPoint(cx, cy+1)].heightMap[0][x];
        }
    }

    if (leftEx){
        for (int y = 0; y < N; y++){
            chunk.heightMap[y][0] = m_chunks[QPoint(cx-1, cy)].heightMap[y][N-1];
        }
    }

    if (rightEx){
        for (int y = 0; y < N; y++){
            chunk.heightMap[y][N-1] = m_chunks[QPoint(cx+1, cy)].heightMap[y][0];
        }
    }


    double scale = m_offset;

    for (int step2 = N - 1; step2 > 1; step2 /= 2)
    {
        scale *= m_roughness;
        int half = step2 / 2;

        // Diamond
        for (int y = 0; y < N - 1; y += step2)
            for (int x = 0; x < N - 1; x += step2) {
                double avg = (chunk.heightMap[y][x] // ерхний левый
                              + chunk.heightMap[y][x+step2] //верхний правый
                              + chunk.heightMap[y+step2][x] //нижний левый
                              + chunk.heightMap[y+step2][x+step2]) * 0.25; //нижний правый, среднее четырёх углов

                chunk.heightMap[y+half][x+half] = avg + chunkRand(rng,-scale, scale); //случайное смещение центра
            }

        // Square
        for (int y = 0; y < N; y += half)
            for (int x = (y/half) % 2 ? 0 : half; x < N; x += step2)
            {
                // пропускаем точки на краях где сосед уже всё задал
                bool onEdge = (topEx    && y == 0)   ||
                              (bottomEx && y == N-1) ||
                              (leftEx   && x == 0)   ||
                              (rightEx  && x == N-1);
                if (onEdge) continue;

                double sum = 0; int cnt = 0;
                if (x-half >= 0) { sum += chunk.heightMap[y][x-half]; cnt++; }
                if (x+half < N)  { sum += chunk.heightMap[y][x+half]; cnt++; }
                if (y-half >= 0) { sum += chunk.heightMap[y-half][x]; cnt++; }
                if (y+half < N)  { sum += chunk.heightMap[y+half][x]; cnt++; }
                if (cnt > 0)
                    chunk.heightMap[y][x] = sum / cnt + chunkRand(rng,-scale, scale);
            }
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



double DiamondSquareGenerate::chunkRand(std::mt19937 &rng, double a, double b)
{
    std::uniform_real_distribution<double> d(a, b);
    return d(rng);
}



double DiamondSquareGenerate::cornerValue(int worldX, int worldY)
{
    int32_t n = (uint32_t)(worldX * 73856093u) ^ (uint32_t)(worldY * 19349663u) ^ m_seed;
    n = (n << 13) ^ n;
    double v = 1.0 - ((n * (n * n * 15731u + 789221u) + 1376312589u)
                      & 0x7fffffff) / 1073741824.0;
    return v * m_offset;
}

QColor DiamondSquareGenerate::heightToColor(double t)
{

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

