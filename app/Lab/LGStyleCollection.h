//
//  LGStyleCollection.h
//  labGraphic
//
//  Created by Ki MNO on 2023/4/4.
//

#ifndef LGStyleCollection_h
#define LGStyleCollection_h

#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtDataVisualization>

// MARK: - 样式：Bar3D

/// 设定阴影质量
enum LG3DShadowQuality {
    ShadowQuality3DNone,
    ShadowQuality3DLow,
    ShadowQuality3DMedium,
    ShadowQuality3DHigh,
    ShadowQuality3DLowSoft,
    ShadowQuality3DMediumSoft,
    ShadowQuality3DHighSoft
};

/// 设定 3DBar 图像的样式
enum LG3DBarConfigBarStyle {
    Bar3DStyleBar,
    Bar3DStylePyramid,
    Bar3DStyleCone,
    Bar3DStyleCylinder,
    Bar3DStyleBevel_Bar,
    Bar3DStyleSphere
    
};

/// 设定 Bar3D 图像的主题
enum LG3DBarConfigTheme {
    Bar3DThemeStyleQt,
    
    
};

/// Bar3D 图像偏好设置
struct LG3DBarConfig {
    
    LG3DBarConfigBarStyle barStyle;
    LG3DBarConfigTheme theme;
    LG3DShadowQuality shadowQuality;
    
    bool showBackground;
    bool showGrid;
    bool smoothBars;
    bool reverseValueAxis;
    
    
};

// MARK: - 2D 图表通用样式


/// 2D 图表类别
enum LG2DDataType {
    Type2DBar,
    Type2DPoint,
    Type2DArea,
    Type2DPie
    
};

/// 2D 图表主题
enum LG2DDataTheme {
    Theme2DLight,
    Theme2DBlueCerulean,
    Theme2DDark,
    Theme2DBrownSand,
    Theme2DBlueSand,
    Theme2DBlueNCS,
    Theme2DHighContrast,
    Theme2DBlueIcy,
    Theme2DThemeQt
};

/// 2D 数据图表动画
enum LG2DDataAnimation {
    Data2DAnimationNoAnimations,
    Data2DAnimationGridAxisAnimation,
    Data2DAnimationSeriesAnimation,
    Data2DAnimationAllAnimation
};

/// 2D 数据标签位置
enum LG2DDataLegendBoxPosition {
    DataLegent2DPositionNoLegend,
    DataLegent2DPositionLegendTop,
    DataLegent2DPositionLegendBottom,
    DataLegent2DPositionLegendLeft,
    DataLegent2DPositionLegendRight
    
};

/// 2D 数据图表配置
struct LG2DDataConfig {
    
    LG2DDataTheme theme;
    LG2DDataAnimation animation;
    LG2DDataLegendBoxPosition legendBoxPosition;
};

/// 启用 2D 图形抗锯齿
static bool LGGRAPHIC_ANTIALIASING = true;
/// 动画设置
static LG2DDataAnimation LGGRAPHIC_ANIMATION = LG2DDataAnimation::Data2DAnimationSeriesAnimation;


#endif /* LGStyleCollection_h */
