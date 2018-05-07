/*
 * Copyright 2014-2018 Real Logic Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package io.aeron.driver;

import io.aeron.driver.media.ReceiveChannelEndpoint;
import io.aeron.protocol.SetupFlyweight;
import org.agrona.concurrent.UnsafeBuffer;

import java.net.InetSocketAddress;

@FunctionalInterface
public interface SetupMessageHandler
{
    /**
     * Handle a Setup Frame
     *
     * @param channelEndpoint from which the message is delivered.
     * @param header          of the Setup Frame in the message (may be re-wrapped if needed)
     * @param buffer          holding the Setup Info (always starts at 0 offset)
     * @param srcAddress      of the Frame
     * @param transportIndex  that the frame arrived on
     */
    void onSetupMessage(
        ReceiveChannelEndpoint channelEndpoint,
        SetupFlyweight header,
        UnsafeBuffer buffer,
        InetSocketAddress srcAddress,
        int transportIndex);
}
