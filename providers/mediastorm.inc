<?php
/**
 * This include processes MediaStorm.com videos for use by emfield.module
 */

define('MEDIA_MEDIASTORM_URL', 'http://mediastorm.com');

/**
 * Implementation of emvideo_PROVIDER_info()
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
    'provider' => 'mediastorm',
    'name' => t('MediaStorm'),
    'url'  => MEDIA_MEDIASTORM_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', 
      array('!provider' => l(t('mediastorm.com'), MEDIA_MEDIASTORM_URL))),
    'supported_features' => $features,
  );
}

function emvideo_mediastorm_settings() {
  $form = array();
  return $form;
}

/**
 * Implementation of emvideo_PROVIDER_extract
 */
function emvideo_mediastorm_extract($embed = '') {
/*
http://mediastorm.com/publication/african-air
<script type="text/javascript" src="http://mediastorm.com/player/embed.php?id=e4eccf159b95f9588110&w=460&h=373&amp;lang=none"></script>
*/

  return array(
    '@mediastorm.com/player/embed.php\?id=([0-9a-zA-Z]+)@i'
  );
}