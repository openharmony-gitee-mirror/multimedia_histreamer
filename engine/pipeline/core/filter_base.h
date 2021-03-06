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

#ifndef HISTREAMER_PIPELINE_CORE_FILTER_BASE_H
#define HISTREAMER_PIPELINE_CORE_FILTER_BASE_H
#include <atomic>
#include <functional>
#include <list>
#include <memory>

#include "filter.h"
#include "foundation/error_code.h"
#include "utils/constants.h"
#include "utils/event.h"
#include "utils/utils.h"
#include "filter_type.h"
#include "port.h"

namespace OHOS {
namespace Media {
namespace Pipeline {
class FilterBase : public Filter {
public:
    explicit FilterBase(std::string name);
    ~FilterBase() override = default;
    void Init(EventReceiver* receiver, FilterCallback* callback) override;
    PInPort GetInPort(const std::string& name) override;
    POutPort GetOutPort(const std::string& name) override;
    const std::string& GetName() override
    {
        return name_;
    }
    const EventReceiver* GetOwnerPipeline() const override
    {
        return eventReceiver_;
    }

    ErrorCode Prepare() override;
    ErrorCode Start() override;
    ErrorCode Pause() override;
    ErrorCode Stop() override;
    ErrorCode Resume() override
    {
        return Start();
    }
    void FlushStart() override
    {
    }
    void FlushEnd() override
    {
    }
    ErrorCode SetParameter(int32_t key, const Plugin::Any& value) override
    {
        UNUSED_VARIABLE(key);
        UNUSED_VARIABLE(value);
        return ErrorCode::ERROR_UNIMPLEMENTED;
    }
    ErrorCode GetParameter(int32_t key, Plugin::Any& value) override
    {
        UNUSED_VARIABLE(key);
        UNUSED_VARIABLE(value);
        return ErrorCode::ERROR_UNIMPLEMENTED;
    }

    void UnlinkPrevFilters() override;

    std::vector<Filter*> GetNextFilters() override;

    ErrorCode PushData(const std::string& inPort, AVBufferPtr buffer) override;
    ErrorCode PullData(const std::string& outPort, uint64_t offset, size_t size, AVBufferPtr& data) override;
    std::vector<WorkMode> GetWorkModes() override
    {
        return {WorkMode::PUSH};
    }

    // Port??????????????????Filter????????????
    void OnEvent(Event event) override;

protected:
    virtual void InitPorts();

    std::string NamePort(const std::string& mime);

    /**
     * ??????routemap??? outPortName?????????inport
     *
     * @param outPortName outport name
     * @return null if not exists
     */
    PInPort GetRouteInPort(const std::string& outPortName);

    /**
     * ??????routemap??? inPortName?????????outport
     *
     * @param inPortName inport name
     * @return null if not exists
     */
    POutPort GetRouteOutPort(const std::string& inPortName);

protected:
    std::string name_;
    std::atomic<FilterState> state_;
    EventReceiver* eventReceiver_;
    FilterCallback* callback_;
    std::vector<PFilter> children_ {};
    std::vector<PInPort> inPorts_ {};
    std::vector<POutPort> outPorts_ {};
    std::vector<PairPort> routeMap_ {}; // inport -> outport

    std::map<std::string, uint32_t> mediaTypeCntMap_ {};

    FilterType filterType_ {FilterType::NONE};

private:
    template <typename T>
    static T FindPort(const std::vector<T>& list, const std::string& name);
};
} // namespace Pipeline
} // namespace Media
} // namespace OHOS
#endif
