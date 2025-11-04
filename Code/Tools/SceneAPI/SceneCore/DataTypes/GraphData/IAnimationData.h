#pragma once

/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Math/Vector3.h>
#include <SceneAPI/SceneCore/DataTypes/IGraphObject.h>
#include <SceneAPI/SceneCore/DataTypes/MatrixType.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace DataTypes
        {
            class IAnimationData
                : public IGraphObject
            {
            public:
                AZ_RTTI(IAnimationData, "{62B0571C-6EFF-42FA-902A-85AC744E04F2}", IGraphObject);
                struct AnimationEntry 
                {
                    AnimationEntry()
                        : m_timeStepBetweenFrames(1.0/30.0)
                        , m_name("default") {}

                    AnimationEntry(const AZStd::string name, double timeStepBetweenFrames)
                        : m_timeStepBetweenFrames(timeStepBetweenFrames)
                        , m_name(name) {}
                        
                    AZStd::string& GetName() { return m_name; }
                    size_t GetKeyFrameCount() const { return m_keyframes.size(); }
                    const MatrixType& GetKeyFrame(size_t index) const{  return m_keyframes[index]; }
                    double GetTimeStepBetweenFrames() const { m_timeStepBetweenFrames; }

                    double m_timeStepBetweenFrames;
                    AZStd::string m_name;
                    AZStd::vector<MatrixType> m_keyframes;
                };
                virtual ~IAnimationData() override = default;

                void CloneAttributesFrom([[maybe_unused]] const IGraphObject* sourceObject) override {}

                virtual size_t GetAnimationStackCount() const = 0;
                virtual bool GetAnimationStackByName(const AZStd::string& name, AnimationEntry& outEntry) const = 0;
                virtual bool GetAnimationStack(size_t index, AnimationEntry& outEntry) = 0;
            };

            class IBlendShapeAnimationData
                : public IGraphObject
            {
            public:
                AZ_RTTI(IBlendShapeAnimationData, "{CD2004EB-8B88-42B2-A539-079A557C98C9}", IGraphObject);

                virtual ~IBlendShapeAnimationData() override = default;

                void CloneAttributesFrom([[maybe_unused]] const IGraphObject* sourceObject) override {}

                virtual const char* GetBlendShapeName() const = 0;
                virtual size_t GetKeyFrameCount() const = 0;
                virtual double GetKeyFrame(size_t index) const = 0;
                virtual double GetTimeStepBetweenFrames() const = 0;
            };
        }
    }
}
