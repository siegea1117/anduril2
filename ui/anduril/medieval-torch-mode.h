// Medieval Torch Mode
#pragma once

#if defined(USE_MEDIEVAL_TORCH_MODE) && defined(MODEL_SOFIRN_SP36)

uint8_t medieval_torch_state(Event event, uint16_t arg);
void medieval_torch_iter(void);

#endif
