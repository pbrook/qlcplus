/*
  Q Light Controller Plus
  video.h

  Copyright (c) Massimo Callegari

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef VIDEO_H
#define VIDEO_H

#include <QMediaPlayer>
#include <QColor>

#include "function.h"

class QDomDocument;
class QVideoWidget;

class Video : public Function
{
    Q_OBJECT
    Q_DISABLE_COPY(Video)

    /*********************************************************************
     * Initialization
     *********************************************************************/
public:
    Video(Doc* doc);
    virtual ~Video();

private:
    Doc *m_doc;
    /*********************************************************************
     * Copying
     *********************************************************************/
public:
    /** @reimpl */
    Function* createCopy(Doc* doc, bool addToDoc = true);

    /** Copy the contents for this function from another function */
    bool copyFrom(const Function* function);

public slots:
    /** Catches Doc::functionRemoved() so that destroyed members can be
        removed immediately. */
    void slotFunctionRemoved(quint32 function);

    /*********************************************************************
     * Capabilities
     *********************************************************************/
public:
    /** Get the list of the extensions supported by the video decoding system */
    static QStringList getCapabilities();

    /** Get the number of available screens in the system */
    static int getScreenCount();

    /*********************************************************************
     * Properties
     *********************************************************************/
public:
    /**
     * Set the time where the Audio object is placed over a timeline
     *
     * @param time The start time in milliseconds of the Audio object
     */
    void setStartTime(quint32 time);

    /**
     * Returns the time where the Audio object is placed over a timeline
     *
     * @return Start time in milliseconds of the Audio object
     */
    quint32 getStartTime() const;

    /**
     * Returns the duration of the source audio file loaded
     *
     * @return Duration in milliseconds of the source audio file
     */
    qint64 getDuration();

    /**
     * Set the color to be used by a AudioItem
     */
    void setColor(QColor color);

    /**
     * Get the color of this Audio object
     */
    QColor getColor();

    /**
     * Set the source file name used by this Video object
     */
    bool setSourceFileName(QString filename);

    /**
     * Retrieve the source file name used by this Video object
     */
    QString getSourceFileName();

    /**
     * Set the screen index where to render the video
     */
    void setScreen(int index);

    /**
     * Retrieve the screen index where the video is rendered
     */
    int screen();

    /**
     * Set the video to be rendered in windowed or fullscreen mode
     */
    void setFullscreen(bool enable);

    /**
     * Retrieves if the video has to be rendered in windowed or fullscreen mode
     */
    bool fullscreen();

    void adjustAttribute(qreal fraction, int attributeIndex);

protected slots:
    void slotStatusChanged(QMediaPlayer::MediaStatus status);
    void slotTotalTimeChanged(qint64 duration);

signals:
    void totalTimeChanged(qint64);
    void metaDataChanged(QString key, QVariant data);

private:
    /** output interface to render video data */
    QMediaPlayer *m_videoPlayer;
    /** Qt widget that actually displays the video */
    QVideoWidget *m_videoWidget;
    /** Absolute start time of video over a timeline (in milliseconds) */
    quint32 m_startTime;
    /** Color to use when displaying the video object in the Show manager */
    QColor m_color;
    /** Name of the source video file */
    QString m_sourceFileName;
    /** Duration of the video content */
    qint64 m_videoDuration;
    /** Resolution of the video content */
    QSize m_resolution;
    /** Index of the screen where to render the video */
    int m_screen;
    /** Flag that indicates if the video has to go fullscreen */
    bool m_fullscreen;

    /*********************************************************************
     * Save & Load
     *********************************************************************/
public:
    /** Save function's contents to an XML document */
    bool saveXML(QDomDocument* doc, QDomElement*);

    /** Load function's contents from an XML document */
    bool loadXML(const QDomElement&);

    /** @reimp */
    void postLoad();

    /*********************************************************************
     * Running
     *********************************************************************/
public:
    /** @reimpl */
    void preRun(MasterTimer*);

    /** @reimpl */
    void write(MasterTimer* timer, QList<Universe*> universes);

    /** @reimpl */
    void postRun(MasterTimer* timer, QList<Universe *> universes);

};

#endif
