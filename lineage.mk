# Inherit framework
$(call inherit-product, vendor/lineage/config/common_full_tablet_wifionly.mk)

# Inherit device configuration
$(call inherit-product, device/actions/gs702a/full_gs702a.mk)

# Inherit GSM common stuff
PRODUCT_COPY_FILES += \
    vendor/lineage/prebuilt/common/etc/apns-conf.xml:system/etc/apns-conf.xml

#Device identifier. This must come after all inclusions
PRODUCT_NAME := lineage_gs702a
PRODUCT_BRAND := Android
PRODUCT_DEVICE := gs702a
PRODUCT_MODEL := Overmax NewBase 2
PRODUCT_MANUFACTURER := overmax
PRODUCT_GMS_CLIENTID_BASE := android-overmax
PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="full_gs702a-userdebug 8.1 eng.disyer test-keys" \
    PRODUCT_NAME=gs702a \
    TARGET_DEVICE=NewBase2

BUILD_FINGERPRINT := Android/full_gs702a/gs702a:4.1.1/JRO03C/eng.zhouzf.20130720.141654:userdebug/test-keys
TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 480
