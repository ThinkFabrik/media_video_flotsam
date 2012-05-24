<?php
/**
 * This include processes MediaStorm.com videos for use by emfield.module
 */

define('MEDIA_MEDIASTORM_URL', 'http://mediastorm.com');
define('MEDIA_MEDIASTORM_PLAYER_URL', 'http://player.mediastorm.com/pub/player/flash/swf/WrapperMSPlayer.swf');
define('MEDIA_MEDIASTORM_IFRAME_URL', 'http://player.mediastorm.com/players/codewriter/flash');

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
  return array(
    '@mediastorm.com/player/embed.php\?id=([0-9a-zA-Z]+)@i',
    '@mediastorm.com/players/embed\?id=([0-9a-zA-Z]+)@i'
  );
}

/**
 * Return a link to MediaStorm
 * Cannot return link to the video because of the custom nature of the embeds
 */
function emvideo_mediastorm_embedded_link() {
  return MEDIA_MEDIASTORM_URL;
}

/**
 * Returns the embedded flash object
 */
function theme_emvideo_mediastorm_video($embed, $width, $height, $mode = 'iframe') {

  if (!$embed) {
    return;
  }

  if ($mode == 'iframe') {
    $src = MEDIA_MEDIASTORM_IFRAME_URL . "?id=$embed&w=$width&h=$height&lang=eng";
    $video_embed = "<iframe src=\"$src\" width=\"{$width}\" height=\"{$height}\" id=\"mediastorm-player-{$embed}\" allowtransparency=\"true\" frameborder=\"0\" scrolling=\"0\"></iframe>";

  }
  else {
    $player = MEDIA_MEDIASTORM_PLAYER_URL;
    $flashvars = "data=http://player.mediastorm.com/players/&amp;referrer=&amp;id=$embed&amp;lang=eng";

    $video_embed = <<<EOD
<embed src="$player" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width=$width height=$height flashvars="$flashvars" wmode="transparent"></embed>
EOD;
  }

  return $video_embed;
}

function emvideo_mediastorm_video($embed, $width, $height, $field, $item, $node, $autoplay) {
  return theme('emvideo_mediastorm_video', $embed, $width, $height, 'iframe');
}

/**
 * Implementation of hook_emfield_subtheme()
 */
function emvideo_mediastorm_emfield_subtheme() {
  return array(
    'emvideo_mediastorm_video' => array(
      'arguments' => array('embed' => NULL, 'width' => NULL, 'height' => NULL, 'mode' => NULL),
      'file' => 'providers/mediastorm.inc'
    ),
  );
}
