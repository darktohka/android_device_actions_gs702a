# Inherit device configuration
$(call inherit-product, device/actions/gs702a/full_gs702a.mk)

# Inherit some common cyanogenmod stuff.
$(call inherit-product, vendor/lineage/config/common_full_tablet_wifionly.mk)

# Inherit GSM common stuff
PRODUCT_COPY_FILES += \
    vendor/lineage/prebuilt/common/etc/apns-conf.xml:system/etc/apns-conf.xml

#Device identifier. This must come after all inclusions
PRODUCT_NAME := lineage_gs702a
PRODUCT_BRAND := Android
PRODUCT_DEVICE := gs702a
PRODUCT_MODEL := Overmax NewBase 2
PRODUCT_MANUFACTURER := overmax

TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 480
