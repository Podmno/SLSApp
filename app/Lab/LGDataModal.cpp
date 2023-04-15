//
//  LGDataModal.cpp
//  labGraphic
//
//  Created by Ki MNO on 2023/4/2.
//

#include "LGDataModal.h"

LGBaseModal::LGBaseModal()
{
    dataType = LGModalType::DataModalUnknown;
}

QStringList LGBaseModal::csvReader(QString filePath)
{
    
    QFile inFile(filePath);
    QStringList lines;
    if (inFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream_text(&inFile);
        while (!stream_text.atEnd())
        {
            lines.push_back(stream_text.readLine());
        }
        inFile.close();
    }
    return lines;
    
}

void LGBaseModal::setAnimationOptions(QChart* chart)
{
    switch(LGGRAPHIC_ANIMATION) {
        case LG2DDataAnimation::Data2DAnimationNoAnimations:
            chart->setAnimationOptions(QChart::NoAnimation);
            break;
        case LG2DDataAnimation::Data2DAnimationSeriesAnimation:
            chart->setAnimationOptions(QChart::SeriesAnimations);
            break;
        case LG2DDataAnimation::Data2DAnimationGridAxisAnimation:
            chart->setAnimationOptions(QChart::GridAxisAnimations);
            break;
        case LG2DDataAnimation::Data2DAnimationAllAnimation:
            chart->setAnimationOptions(QChart::AllAnimations);
            break;
        default:
            chart->setAnimationOptions(QChart::NoAnimation);
            break;
    }
    
}


LG2DBarModal::LG2DBarModal()
{
    dataType = LGModalType::DataModalBar2D;
}

bool LG2DBarModal::importFromCSV(QString filePath)
{

    QStringList lines = csvReader(filePath);

    QStringList split_title = lines.at(0).split(",");
    for(int n = 0; n < split_title.size(); n++) {
        LGBarSeries series_data;
        series_data.title = split_title.at(n);
        seriesData.append(series_data);
    }
        
    for (int j = 1; j < lines.size(); j++)
    {
        QString line = lines.at(j);
        QStringList split = line.split(",");
        for (int col = 0; col < split.size(); col++)
        {
            //cout << split.at(col).toStdString() << " ";
            QString data = split.at(col);
            double d = data.toDouble();
            seriesData[j-1].barData.append(d);
        }
    }
    
    return true;
        
}

QChart* LG2DBarModal::getChart()
{

    QChart* chart = new QChart();
    chart->setTitle(title);
   
    if(dataType == LGModalType::DataModalBar2D) {
        QBarSeries* series_bar = new QBarSeries();
        
        for(LGBarSeries sdata : seriesData) {

            QBarSet* set = new QBarSet(sdata.title);
            for(double value : sdata.barData) {
                set->append(value);
            }
            
            series_bar->append(set);
            
        }
        
        chart->addSeries(series_bar);
    }
    
    if(dataType == LGModalType::DataModalPie2D) {
        QPieSeries* series_pie = new QPieSeries();
        
        for(LGBarSeries sdata : seriesData) {
            series_pie->append(sdata.title, sdata.barData[0]);
        }
        chart->addSeries(series_pie);
    }
    
    chart->createDefaultAxes();
    setAnimationOptions(chart);
    
    return chart;
}

LG2DPointModal::LG2DPointModal()
{
    dataType = LGModalType::DataModalLine2D;
}
    
bool LG2DPointModal::importFromCSV(QString filePath)
{
    QStringList lines = csvReader(filePath);

    QStringList split_title = lines.at(0).split(",");
    for(int n = 0; n < split_title.size(); n++) {
        LG2DPointSeries series_data;
        series_data.title = split_title.at(n);
        seriesData.append(series_data);
    }
        
    for (int j = 1; j < lines.size(); j++)
    {
        QString line = lines.at(j);
        line.replace("(","");
        line.replace(")","");
        QStringList num_list = line.split(",");
        bool record = false;
        double record_number = 0.0;
        for(QString double_num : num_list) {
            if(record == true) {
                LG2DPoint pt;
                pt.x = record_number;
                pt.y = double_num.toDouble();
                seriesData[j-1].pointData.append(pt);
                record = false;
            } else {
                record_number = double_num.toDouble();
                record = true;
            }
        }
        
    }
    return true;
    
}

QChart* LG2DPointModal::getChart()
{
    QChart* chart = new QChart();
    chart->setTitle(title);
   
    if(dataType == LGModalType::DataModalLine2D) {
        for(LG2DPointSeries sdata : seriesData) {
            QLineSeries* series_line = new QLineSeries();
            series_line->setName(sdata.title);
            for(LG2DPoint pt : sdata.pointData) {
                series_line->append(pt.x, pt.y);
            }
            chart->addSeries(series_line);
            
        }
        
        chart->createDefaultAxes();
        setAnimationOptions(chart);
    }
    
    if(dataType == LGModalType::DataModalArea2D) {
        for(LG2DPointSeries sdata : seriesData) {
            QAreaSeries* area = new QAreaSeries();
            area->setName(sdata.title);
            QLineSeries* series_line = new QLineSeries();
            
            for(LG2DPoint pt : sdata.pointData) {
                series_line->append(pt.x, pt.y);
                
            }
            area->setLowerSeries(0);
            area->setUpperSeries(series_line);
            chart->addSeries(area);
            
        }
        
        chart->createDefaultAxes();
        setAnimationOptions(chart);
    }
    
    
    return chart;
}


LG3DBarModal::LG3DBarModal()
{
    
    dataType = LGModalType::DataModalBar3D;
}

bool LG3DBarModal::importFromCSV(QString filePath)
{
    QStringList lines = csvReader(filePath);

    QStringList split_title = lines.at(0).split(",");
    for(int n = 0; n < split_title.size(); n++) {
        LGBarSeries series_data;
        series_data.title = split_title.at(n);
        seriesData.append(series_data);
    }
        
    for (int j = 1; j < lines.size(); j++)
    {
        QString line = lines.at(j);
        QStringList split = line.split(",");
        for (int col = 0; col < split.size(); col++)
        {
            //cout << split.at(col).toStdString() << " ";
            QString data = split.at(col);
            double d = data.toDouble();
            seriesData[j-1].barData.append(d);
        }
    }
    
}

Q3DBars* LG3DBarModal::get3DBars()
{
    
    // TODO: Series 表示不正确
    
    Q3DBars* bars = new Q3DBars();
    
    for(LGBarSeries modal : seriesData) {
        
        QBar3DSeries* bar_series = new QBar3DSeries();
        QBarDataRow* row_data = new QBarDataRow();
        
        
        for(double number : modal.barData) {
            row_data->append(number);
        }
        
        bar_series->dataProxy()->addRow(row_data);
        bars->addSeries(bar_series);
        
    }
    
    return bars;
    
}
