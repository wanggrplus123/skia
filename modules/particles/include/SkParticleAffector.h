/*
* Copyright 2019 Google LLC
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef SkParticleAffector_DEFINED
#define SkParticleAffector_DEFINED

#include "SkReflected.h"

#include "SkPoint.h"

struct SkColorCurve;
struct SkCurve;
struct SkParticleState;
struct SkParticleUpdateParams;

enum SkParticleFrame {
    kWorld_ParticleFrame,     // "Up" is { 0, -1 }
    kLocal_ParticleFrame,     // "Up" is particle's heading
    kVelocity_ParticleFrame,  // "Up" is particle's direction of travel
};

class SkParticleAffector : public SkReflected {
public:
    REFLECTED_ABSTRACT(SkParticleAffector, SkReflected)

    void apply(SkParticleUpdateParams& params, SkParticleState ps[], int count);
    void visitFields(SkFieldVisitor* v) override;

    static void RegisterAffectorTypes();

    // Affectors that can set the linear or angular velocity. Both have a 'force' option to apply
    // the resulting value as a force, rather than directly setting the velocity.
    static sk_sp<SkParticleAffector> MakeLinearVelocity(const SkCurve& angle,
                                                        const SkCurve& strength,
                                                        bool force,
                                                        SkParticleFrame frame);
    static sk_sp<SkParticleAffector> MakeAngularVelocity(const SkCurve& strength,
                                                         bool force);

    // Set the orientation of a particle, relative to the world, local, or velocity frame.
    static sk_sp<SkParticleAffector> MakeOrientation(const SkCurve& angle,
                                                     SkParticleFrame frame);

    static sk_sp<SkParticleAffector> MakePointForce(SkPoint point, SkScalar constant,
                                                    SkScalar invSquare);

    static sk_sp<SkParticleAffector> MakeSize(const SkCurve& curve);
    static sk_sp<SkParticleAffector> MakeFrame(const SkCurve& curve);
    static sk_sp<SkParticleAffector> MakeColor(const SkColorCurve& curve);

private:
    virtual void onApply(SkParticleUpdateParams& params, SkParticleState ps[], int count) = 0;

    bool fEnabled = true;
};

#endif // SkParticleAffector_DEFINED