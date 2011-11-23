<?php
/**
 * This include processes MediaStorm.com videos for use by emfield.module
 */

define('MEDIA_MEDIASTORM_URL', 'http://mediastorm.com');
/**
 * Implementation of hook_PROVIDER_info()
 */
 function emvideo_mediastorm_info() {
  $features = array(
    array(t('Autoplay'), t('No'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('No'), t('')),
    array(
      t('Full screen mode'),
      t('Yes'),
      t('You may customize the player to enable or disable full screen playback. Full screen mode is enabled by default.')),
  );
  
  return array(
    'provider' => t('mediastorm'),
    'name' => t('MediaStorm'),
    'url'  => MEDIA_MEDIASTORM_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', 
      array('!provider' => l(t('mediastorm.com'), MEDIA_MEDIASTORM_URL))),
    'supported_features' => $features,
  );
}