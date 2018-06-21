# Inherit framework
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit device configuration
$(call inherit-product, device/actions/gs702a/gs702a.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

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

BUILD_FINGERPRINT := Android/full_gs702a/gs702a:4.1.1/JRO03C/eng.zhouzf.20130720.141654:userdebug/test-keys
TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 480
