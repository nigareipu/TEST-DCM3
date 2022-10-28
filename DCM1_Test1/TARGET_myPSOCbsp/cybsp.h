
#pragma once

#include "cy_result.h"
#include "cybsp_types.h"
#if defined(CYBSP_WIFI_CAPABLE) && defined(CY_USING_HAL)
#include "cyhal_sdio.h"
#endif
#if defined(COMPONENT_WICED_BLE) || defined(COMPONENT_WICED_DUALMODE)
#include "cybsp_bt_config.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/** Failed to configure sysclk power management callback */
#define CYBSP_RSLT_ERR_SYSCLK_PM_CALLBACK  \
		(CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_BSP, 0))



cy_rslt_t cybsp_init(void);

#if defined(CYBSP_WIFI_CAPABLE) && defined(CY_USING_HAL)

#define CYBSP_WIFI_INTERFACE_TYPE        CYBSP_SDIO_INTERFACE

/**
 * \brief Get the initialized sdio object used for communicating with the WiFi Chip.
 * \note This function should only be called after cybsp_init();
 * \returns The initialized sdio object.
 */
cyhal_sdio_t* cybsp_get_wifi_sdio_obj(void);
#endif // defined(CYBSP_WIFI_CAPABLE)

/** \} group_bsp_functions */

#ifdef __cplusplus
}
#endif // __cplusplus
