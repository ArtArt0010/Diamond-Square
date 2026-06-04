#ifndef MID_POINT_DISPLACMENT_H
#define MID_POINT_DISPLACMENT_H
#include <QQuickPaintedItem>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <random>
#include<QHash>


struct Chunk {
    int cx, cy;
    QVector<QVector<double>> heightMap;
    bool generated = false;
};


class DiamondSquareGenerate : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    QML_NAMED_ELEMENT(DiamondSquare)


    Q_PROPERTY(double waterLevel READ waterLevel WRITE setWaterLevel NOTIFY waterLevelChanged)
    Q_PROPERTY(double roughness READ roughness WRITE setRoughness NOTIFY roughnessChanged)
    Q_PROPERTY(quint32 seed READ seed WRITE setSeed NOTIFY seedChanged)


    Q_PROPERTY(double camX READ camX WRITE setCamX NOTIFY camChanged)
    Q_PROPERTY(double camY READ camY WRITE setCamY NOTIFY camChanged)
    Q_PROPERTY(double camScale READ camScale WRITE setCamScale NOTIFY camChanged)


public:
    explicit DiamondSquareGenerate(QQuickItem *parent = nullptr);
    double roughness() const{return m_roughness;}
    void setRoughness(double v);
    double waterLevel() const { return m_waterLevel; }
    void setWaterLevel(double v);
    quint32 seed() const { return m_seed; }
    void setSeed(quint32 s);
    double camX() const { return m_camX; }
    double camY() const { return m_camY; }
    double camScale() const { return m_camScale; }
    void setCamX(double x);
    void setCamY(double y);
    void setCamScale(double v);
    void paint(QPainter *painter) override;



signals:
    void offsetChanged();
    void roughnessChanged();
    void seedChanged();
    void waterLevelChanged();
    void camChanged();



private:

    Chunk generateChunk(int cx, int cy);
    void updateChanks();
    double chunkRand(std::mt19937 &rng, double a, double b);

    double cornerValue(int worldX, int worldY);


    QColor heightToColor(double t);
    void componentComplete() override;


private:

    double m_roughness = 0.5;      // шероховатость
    double m_offset = 150.0;       // начальная амплитуда
    double m_waterLevel = 0.5;
    int m_chunkSize = 33;
    int m_viewRadius = 2;

    quint32 m_seed = 12345;

    double m_camX = 0.0;
    double m_camY = 0.0;
    double m_camScale = 4.0;
    QHash<QPoint, Chunk> m_chunks;
};
#endif // DIAMONDSQUAREGENERATE_H
