/*
 * Copyright (c) 2021-2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HISTREAMER_FFMPEG_UTILS_H
#define HISTREAMER_FFMPEG_UTILS_H

#include <string>
#include <type_traits>
#include "foundation/type_define.h"
#include "plugin/common/plugin_audio_tags.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavutil/error.h"
#include "libavutil/frame.h"
#ifdef __cplusplus
};
#endif

namespace OHOS {
namespace Media {
namespace Plugin {
std::string AVStrError(int errnum);

/**
 * Convert time from ffmpeg to time in us.
 * @param pts ffmpeg time
 * @param base ffmpeg time_base
 * @return time in milliseconds
 */
uint64_t ConvertTimeFromFFmpeg(int64_t pts, AVRational base);

/**
 * Convert time in milliseconds to ffmpeg time.
 * @param time time in milliseconds
 * @param base ffmpeg time_base
 * @return time in ffmpeg.
 */
int64_t ConvertTimeToFFmpeg(int64_t timestampUs, AVRational base);

/*
 * Fill in pointers in an AVFrame, aligned by 4 (required by X).
 */
int FillAVPicture(AVFrame* picture, uint8_t* ptr, enum AVPixelFormat pixFmt, int width, int height);

/*
 * Get the size of an picture
 */
int GetAVPictureSize(int pixFmt, int width, int height);

void RemoveDelimiter(char delimiter, std::string& str);

std::string RemoveDelimiter(const char* str, char delimiter);

void ReplaceDelimiter(const std::string& delmiters, char newDelimiter, std::string& str);

std::vector<std::string> SplitString(const char* str, char delimiter);

std::vector<std::string> SplitString(const std::string& string, char delimiter);

AudioSampleFormat Trans2Format(AVSampleFormat sampleFormat);

AVSampleFormat Trans2FFmepgFormat(AudioSampleFormat sampleFormat, bool interleaved);

AudioChannelLayout ConvertChannelLayoutFromFFmpeg(int channels, uint64_t ffChannelLayout);

uint64_t ConvertChannelLayoutToFFmpeg(AudioChannelLayout channelLayout);
} // namespace Plugin
} // namespace Media
} // namespace OHOS
#endif // HISTREAMER_FFMPEG_UTILS_H
