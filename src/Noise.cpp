/*
 * Crunch Engine 3
 * Copyright 2026 Dodwell Industries
 *
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
#include <Crunch/Noise.hpp>
#include <cmath>
#include <cstdint>

namespace Crunch::TerrainTools {

float GenerateIndividualNoiseValue(uint32_t seed, float x, float y) {
    float noise = std::sin(x * 0.01f) * std::cos(y * 0.01f) * 5.0f;
    return noise;
}

}
