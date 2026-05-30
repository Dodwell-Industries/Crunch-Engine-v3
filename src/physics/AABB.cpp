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
#include <Crunch/physics/AABB.hpp>

namespace Crunch::Physics {

bool Intersects(const AABB& other)
{
    return (
        max.x > other.min.x &&
        min.x < other.max.x &&

        max.y > other.min.y &&
        min.y < other.max.y &&

        max.z > other.min.z &&
        min.z < other.max.z
    );
}
};
