/* FluidSynth - A Software Synthesizer
 *
 * Copyright (C) 2003  Peter Hanappe and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *  
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */

#ifndef _FLUIDSYNTH_SYNTH_H
#define _FLUIDSYNTH_SYNTH_H


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file synth.h
 * @brief Embeddable SoundFont synthesizer
 *  
 * You create a new synthesizer with new_fluid_synth() and you destroy
 * if with delete_fluid_synth(). Use the settings structure to specify
 * the synthesizer characteristics. 
 *
 * You have to load a SoundFont in order to hear any sound. For that
 * you use the fluid_synth_sfload() function.
 *
 * You can use the audio driver functions described below to open
 * the audio device and create a background audio thread.
 *  
 * The API for sending MIDI events is probably what you expect:
 * fluid_synth_noteon(), fluid_synth_noteoff(), ...
 */


FLUIDSYNTH_API fluid_synth_t* new_fluid_synth(fluid_settings_t* settings);
FLUIDSYNTH_API void delete_fluid_synth(fluid_synth_t* synth);
FLUIDSYNTH_API fluid_settings_t* fluid_synth_get_settings(fluid_synth_t* synth);

/* MIDI channel messages */

FLUIDSYNTH_API int fluid_synth_noteon(fluid_synth_t* synth, int chan, int key, int vel);
FLUIDSYNTH_API int fluid_synth_noteoff(fluid_synth_t* synth, int chan, int key);
FLUIDSYNTH_API int fluid_synth_cc(fluid_synth_t* synth, int chan, int ctrl, int val);
FLUIDSYNTH_API int fluid_synth_get_cc(fluid_synth_t* synth, int chan, int ctrl, int* pval);
FLUIDSYNTH_API int fluid_synth_sysex(fluid_synth_t *synth, const char *data, int len,
                                     char *response, int *response_len, int *handled, int dryrun);
FLUIDSYNTH_API int fluid_synth_pitch_bend(fluid_synth_t* synth, int chan, int val);
FLUIDSYNTH_API int fluid_synth_get_pitch_bend(fluid_synth_t* synth, int chan, int* ppitch_bend);
FLUIDSYNTH_API int fluid_synth_pitch_wheel_sens(fluid_synth_t* synth, int chan, int val);
FLUIDSYNTH_API int fluid_synth_get_pitch_wheel_sens(fluid_synth_t* synth, int chan, int* pval);
FLUIDSYNTH_API int fluid_synth_program_change(fluid_synth_t* synth, int chan, int program);
FLUIDSYNTH_API int fluid_synth_channel_pressure(fluid_synth_t* synth, int chan, int val);
FLUIDSYNTH_API int fluid_synth_key_pressure(fluid_synth_t* synth, int chan, int key, int val);
FLUIDSYNTH_API int fluid_synth_bank_select(fluid_synth_t* synth, int chan, unsigned int bank);
FLUIDSYNTH_API int fluid_synth_sfont_select(fluid_synth_t* synth, int chan, unsigned int sfont_id);
FLUIDSYNTH_API
int fluid_synth_program_select(fluid_synth_t* synth, int chan, unsigned int sfont_id,
                               unsigned int bank_num, unsigned int preset_num);
FLUIDSYNTH_API int
fluid_synth_program_select_by_sfont_name (fluid_synth_t* synth, int chan,
                                          const char *sfont_name, unsigned int bank_num,
                                          unsigned int preset_num);
FLUIDSYNTH_API 
int fluid_synth_get_program(fluid_synth_t* synth, int chan, unsigned int* sfont_id, 
                            unsigned int* bank_num, unsigned int* preset_num);
FLUIDSYNTH_API int fluid_synth_unset_program (fluid_synth_t *synth, int chan);
FLUIDSYNTH_API int fluid_synth_program_reset(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_system_reset(fluid_synth_t* synth);

FLUIDSYNTH_API int fluid_synth_all_notes_off(fluid_synth_t* synth, int chan);
FLUIDSYNTH_API int fluid_synth_all_sounds_off(fluid_synth_t* synth, int chan);

/**
 * The midi channel type used by fluid_synth_set_channel_type()
 */
enum fluid_midi_channel_type
{
  CHANNEL_TYPE_MELODIC = 0, /**< Melodic midi channel */
  CHANNEL_TYPE_DRUM = 1 /**< Drum midi channel */
};

FLUIDSYNTH_API int fluid_synth_set_channel_type(fluid_synth_t* synth, int chan, int type);


/* Low level access */
FLUIDSYNTH_API fluid_preset_t* fluid_synth_get_channel_preset(fluid_synth_t* synth, int chan);
FLUIDSYNTH_API int fluid_synth_start(fluid_synth_t* synth, unsigned int id, 
				     fluid_preset_t* preset, int audio_chan, 
				     int midi_chan, int key, int vel);
FLUIDSYNTH_API int fluid_synth_stop(fluid_synth_t* synth, unsigned int id);


/* SoundFont management */

FLUIDSYNTH_API 
int fluid_synth_sfload(fluid_synth_t* synth, const char* filename, int reset_presets);
FLUIDSYNTH_API int fluid_synth_sfreload(fluid_synth_t* synth, unsigned int id);
FLUIDSYNTH_API int fluid_synth_sfunload(fluid_synth_t* synth, unsigned int id, int reset_presets);
FLUIDSYNTH_API int fluid_synth_add_sfont(fluid_synth_t* synth, fluid_sfont_t* sfont);
FLUIDSYNTH_API void fluid_synth_remove_sfont(fluid_synth_t* synth, fluid_sfont_t* sfont);
FLUIDSYNTH_API int fluid_synth_sfcount(fluid_synth_t* synth);
FLUIDSYNTH_API fluid_sfont_t* fluid_synth_get_sfont(fluid_synth_t* synth, unsigned int num);
FLUIDSYNTH_API fluid_sfont_t* fluid_synth_get_sfont_by_id(fluid_synth_t* synth, unsigned int id);
FLUIDSYNTH_API fluid_sfont_t *fluid_synth_get_sfont_by_name (fluid_synth_t* synth,
                                                             const char *name);
FLUIDSYNTH_API int fluid_synth_set_bank_offset(fluid_synth_t* synth, int sfont_id, int offset);
FLUIDSYNTH_API int fluid_synth_get_bank_offset(fluid_synth_t* synth, int sfont_id);


/* Reverb  */


FLUIDSYNTH_API int fluid_synth_set_reverb(fluid_synth_t* synth, double roomsize, 
					 double damping, double width, double level);
FLUIDSYNTH_API int fluid_synth_set_reverb_roomsize(fluid_synth_t* synth, double roomsize);
FLUIDSYNTH_API int fluid_synth_set_reverb_damp(fluid_synth_t* synth, double damping);
FLUIDSYNTH_API int fluid_synth_set_reverb_width(fluid_synth_t* synth, double width);
FLUIDSYNTH_API int fluid_synth_set_reverb_level(fluid_synth_t* synth, double level);

FLUIDSYNTH_API void fluid_synth_set_reverb_on(fluid_synth_t* synth, int on);
FLUIDSYNTH_API double fluid_synth_get_reverb_roomsize(fluid_synth_t* synth);
FLUIDSYNTH_API double fluid_synth_get_reverb_damp(fluid_synth_t* synth);
FLUIDSYNTH_API double fluid_synth_get_reverb_level(fluid_synth_t* synth);
FLUIDSYNTH_API double fluid_synth_get_reverb_width(fluid_synth_t* synth);

#define FLUID_REVERB_DEFAULT_ROOMSIZE 0.2f      /**< Default reverb room size */
#define FLUID_REVERB_DEFAULT_DAMP 0.0f          /**< Default reverb damping */
#define FLUID_REVERB_DEFAULT_WIDTH 0.5f         /**< Default reverb width */
#define FLUID_REVERB_DEFAULT_LEVEL 0.9f         /**< Default reverb level */


/* Chorus */

/**
 * Chorus modulation waveform type.
 */
enum fluid_chorus_mod {
  FLUID_CHORUS_MOD_SINE = 0,            /**< Sine wave chorus modulation */
  FLUID_CHORUS_MOD_TRIANGLE = 1         /**< Triangle wave chorus modulation */
};

FLUIDSYNTH_API int fluid_synth_set_chorus(fluid_synth_t* synth, int nr, double level,
					 double speed, double depth_ms, int type);
FLUIDSYNTH_API int fluid_synth_set_chorus_nr(fluid_synth_t* synth, int nr);
FLUIDSYNTH_API int fluid_synth_set_chorus_level(fluid_synth_t* synth, double level);
FLUIDSYNTH_API int fluid_synth_set_chorus_speed(fluid_synth_t* synth, double speed);
FLUIDSYNTH_API int fluid_synth_set_chorus_depth(fluid_synth_t* synth, double depth_ms);
FLUIDSYNTH_API int fluid_synth_set_chorus_type(fluid_synth_t* synth, int type);

FLUIDSYNTH_API void fluid_synth_set_chorus_on(fluid_synth_t* synth, int on);
FLUIDSYNTH_API int fluid_synth_get_chorus_nr(fluid_synth_t* synth);
FLUIDSYNTH_API double fluid_synth_get_chorus_level(fluid_synth_t* synth);
FLUIDSYNTH_API double fluid_synth_get_chorus_speed_Hz(fluid_synth_t* synth);
FLUIDSYNTH_API double fluid_synth_get_chorus_depth_ms(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_get_chorus_type(fluid_synth_t* synth); /* see fluid_chorus_mod */

#define FLUID_CHORUS_DEFAULT_N 3                                /**< Default chorus voice count */
#define FLUID_CHORUS_DEFAULT_LEVEL 2.0f                         /**< Default chorus level */
#define FLUID_CHORUS_DEFAULT_SPEED 0.3f                         /**< Default chorus speed */
#define FLUID_CHORUS_DEFAULT_DEPTH 8.0f                         /**< Default chorus depth */
#define FLUID_CHORUS_DEFAULT_TYPE FLUID_CHORUS_MOD_SINE         /**< Default chorus waveform type */


/* Audio and MIDI channels */

FLUIDSYNTH_API int fluid_synth_count_midi_channels(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_count_audio_channels(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_count_audio_groups(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_count_effects_channels(fluid_synth_t* synth);


/* Synthesis parameters */

FLUIDSYNTH_API void fluid_synth_set_sample_rate(fluid_synth_t* synth, float sample_rate);
FLUIDSYNTH_API void fluid_synth_set_gain(fluid_synth_t* synth, float gain);
FLUIDSYNTH_API float fluid_synth_get_gain(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_set_polyphony(fluid_synth_t* synth, int polyphony);
FLUIDSYNTH_API int fluid_synth_get_polyphony(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_get_active_voice_count(fluid_synth_t* synth);
FLUIDSYNTH_API int fluid_synth_get_internal_bufsize(fluid_synth_t* synth);

FLUIDSYNTH_API 
int fluid_synth_set_interp_method(fluid_synth_t* synth, int chan, int interp_method);

/**
 * Synthesis interpolation method.
 */
enum fluid_interp {
  FLUID_INTERP_NONE = 0,        /**< No interpolation: Fastest, but questionable audio quality */
  FLUID_INTERP_LINEAR = 1,      /**< Straight-line interpolation: A bit slower, reasonable audio quality */
  FLUID_INTERP_4THORDER = 4,    /**< Fourth-order interpolation, good quality, the default */
  FLUID_INTERP_7THORDER = 7,    /**< Seventh-order interpolation */
  
  FLUID_INTERP_DEFAULT = FLUID_INTERP_4THORDER, /**< Default interpolation method */
  FLUID_INTERP_HIGHEST = FLUID_INTERP_7THORDER, /**< Highest interpolation method */
};

/* Generator interface */

FLUIDSYNTH_API int fluid_synth_set_gen (fluid_synth_t* synth, int chan,
                                         int param, float value);
FLUIDSYNTH_API int fluid_synth_set_gen2 (fluid_synth_t* synth, int chan,
                                         int param, float value,
                                         int absolute, int normalized);
FLUIDSYNTH_API float fluid_synth_get_gen(fluid_synth_t* synth, int chan, int param);


/* Tuning */

FLUIDSYNTH_API
int fluid_synth_activate_key_tuning(fluid_synth_t* synth, int bank, int prog,
                                    const char* name, const double* pitch, int apply);
FLUIDSYNTH_API
int fluid_synth_activate_octave_tuning(fluid_synth_t* synth, int bank, int prog,
                                       const char* name, const double* pitch, int apply);
FLUIDSYNTH_API 
int fluid_synth_tune_notes(fluid_synth_t* synth, int bank, int prog,
			   int len, const int *keys, const double* pitch, int apply);
FLUIDSYNTH_API
int fluid_synth_activate_tuning(fluid_synth_t* synth, int chan, int bank, int prog,
                                int apply);
FLUIDSYNTH_API
int fluid_synth_deactivate_tuning(fluid_synth_t* synth, int chan, int apply);
FLUIDSYNTH_API void fluid_synth_tuning_iteration_start(fluid_synth_t* synth);
FLUIDSYNTH_API 
int fluid_synth_tuning_iteration_next(fluid_synth_t* synth, int* bank, int* prog);
FLUIDSYNTH_API int fluid_synth_tuning_dump(fluid_synth_t* synth, int bank, int prog, 
					   char* name, int len, double* pitch);

/* Misc */

FLUIDSYNTH_API double fluid_synth_get_cpu_load(fluid_synth_t* synth);
FLUIDSYNTH_API char* fluid_synth_error(fluid_synth_t* synth);


/* Default modulators */

/**
 * Enum used with fluid_synth_add_default_mod() to specify how to handle duplicate modulators.
 */
enum fluid_synth_add_mod {
  FLUID_SYNTH_OVERWRITE,        /**< Overwrite any existing matching modulator */
  FLUID_SYNTH_ADD,              /**< Add (sum) modulator amounts */
};

FLUIDSYNTH_API int fluid_synth_add_default_mod(fluid_synth_t* synth, fluid_mod_t* mod, int mode);
FLUIDSYNTH_API int fluid_synth_remove_default_mod(fluid_synth_t* synth, const fluid_mod_t* mod);


/*
 * Synthesizer plugin
 *
 * To create a synthesizer plugin, create the synthesizer as
 * explained above. Once the synthesizer is created you can call
 * any of the functions below to get the audio. 
 */

FLUIDSYNTH_API int fluid_synth_write_s16(fluid_synth_t* synth, int len, 
				       void* lout, int loff, int lincr, 
				       void* rout, int roff, int rincr);
FLUIDSYNTH_API int fluid_synth_write_float(fluid_synth_t* synth, int len, 
					 void* lout, int loff, int lincr, 
					 void* rout, int roff, int rincr);
FLUIDSYNTH_API int fluid_synth_nwrite_float(fluid_synth_t* synth, int len, 
					  float** left, float** right, 
					  float** fx_left, float** fx_right);
FLUIDSYNTH_API int fluid_synth_process(fluid_synth_t* synth, int len,
				     int nin, float** in, 
				     int nout, float** out);

/**
 * Type definition of the synthesizer's audio callback function.
 * @param synth FluidSynth instance
 * @param len Count of audio frames to synthesize
 * @param out1 Array to store left channel of audio to
 * @param loff Offset index in 'out1' for first sample
 * @param lincr Increment between samples stored to 'out1'
 * @param out2 Array to store right channel of audio to
 * @param roff Offset index in 'out2' for first sample
 * @param rincr Increment between samples stored to 'out2'
 */
typedef int (*fluid_audio_callback_t)(fluid_synth_t* synth, int len, 
				     void* out1, int loff, int lincr, 
				     void* out2, int roff, int rincr);

/* Synthesizer's interface to handle SoundFont loaders */

FLUIDSYNTH_API void fluid_synth_add_sfloader(fluid_synth_t* synth, fluid_sfloader_t* loader);
FLUIDSYNTH_API fluid_voice_t* fluid_synth_alloc_voice(fluid_synth_t* synth, 
                                                      fluid_sample_t* sample,
                                                      int channum, int key, int vel);
FLUIDSYNTH_API void fluid_synth_start_voice(fluid_synth_t* synth, fluid_voice_t* voice);
FLUIDSYNTH_API void fluid_synth_get_voicelist(fluid_synth_t* synth,
                                              fluid_voice_t* buf[], int bufsize, int ID);
FLUIDSYNTH_API int fluid_synth_handle_midi_event(void* data, fluid_midi_event_t* event);

/* LADSPA */

FLUIDSYNTH_API fluid_ladspa_fx_t *fluid_synth_get_ladspa_fx(fluid_synth_t *synth);


/* API: Poly mono mode */

/* Interface to poly/mono mode variables */
enum fluid_channel_mode_flags
{
    /* channel mode bits */
    FLUID_CHANNEL_POLY_OFF = 0x01, /**< if flag set the basic channel is in mono on state, if not set poly is on */
    FLUID_CHANNEL_OMNI_OFF = 0x02, /**< if flag set the basic channel is in omni on state, if not set omni is off */
    
    FLUID_CHANNEL_BASIC = 0x04,    /**< if flag set the corresponding midi channel is a basic channel */
    FLUID_CHANNEL_ENABLED = 0x08,  /**< if flag set the corresponding midi channel is enabled, else disabled, i.e. channel ignores any MIDI messages */
};

/* breath mode bits infos */
enum fluid_channel_breath_flags
{
    FLUID_CHANNEL_BREATH_POLY = 0x10,  /**< when channel is poly, if flag set the default velocity to initial Attenuation modulator is replaced by a breath modulator */
    FLUID_CHANNEL_BREATH_MONO = 0x20,  /**< when channel is mono, if flag set the default velocity to initial Attenuation modulator is replaced by a breath modulator */
    FLUID_CHANNEL_BREATH_SYNC = 0x40,  /**< when channel is mono, if flag set the breath controler(MSB)triggers noteon/noteoff on the running note */
};

enum fluid_basic_channel_modes
{  
    FLUID_CHANNEL_MODE_MASK = (FLUID_CHANNEL_OMNI_OFF | FLUID_CHANNEL_POLY_OFF), /**< Mask Poly and Omni bits of #fluid_channel_mode_flags */
    FLUID_CHANNEL_MODE_OMNION_POLY = FLUID_CHANNEL_MODE_MASK & (~FLUID_CHANNEL_OMNI_OFF & ~FLUID_CHANNEL_POLY_OFF), /**< MIDI mode 0 */
    FLUID_CHANNEL_MODE_OMNION_MONO = FLUID_CHANNEL_MODE_MASK & (~FLUID_CHANNEL_OMNI_OFF & FLUID_CHANNEL_POLY_OFF), /**< MIDI mode 1 */
    FLUID_CHANNEL_MODE_OMNIOFF_POLY = FLUID_CHANNEL_MODE_MASK & (FLUID_CHANNEL_OMNI_OFF & ~FLUID_CHANNEL_POLY_OFF), /**< MIDI mode 2 */
    FLUID_CHANNEL_MODE_OMNIOFF_MONO = FLUID_CHANNEL_MODE_MASK & (FLUID_CHANNEL_OMNI_OFF | FLUID_CHANNEL_POLY_OFF), /**< MIDI mode 3 */
    FLUID_CHANNEL_MODE_LAST /**< @internal Value defines the count of basic channel modes (#fluid_basic_channel_modes) @warning This symbol is not part of the public API and ABI stability guarantee and may change at any time! */
};

struct _fluid_basic_channel_infos_t
{
	int basicchan;  /**< MIDI channel numer to set as basic channel */
	int mode;       /**< indicates the mode this basic channel is set to (see #fluid_channel_mode_flags) */
	int val;        /**< Number of monophonic channel (Mode 3) */
};
typedef struct  _fluid_basic_channel_infos_t   fluid_basic_channel_infos_t;

FLUIDSYNTH_API int fluid_synth_get_basic_channels( fluid_synth_t* synth,
                                                   fluid_basic_channel_infos_t **basicChannelInfos);
FLUIDSYNTH_API int fluid_synth_reset_basic_channels(fluid_synth_t* synth, int n, 
                                                    fluid_basic_channel_infos_t *basicChannelInfos);
FLUIDSYNTH_API int fluid_synth_get_channel_mode(fluid_synth_t* synth, int chan,
                                                fluid_basic_channel_infos_t  *modeInfos);
FLUIDSYNTH_API int fluid_synth_set_basic_channel(fluid_synth_t* synth, 
                                                 int basicchan, int mode, int val);
/* Interface to mono legato mode  */
/* n1,n2,n3,.. is a legato passage. n1 is the first note, and n2,n3,n4 are played
 legato with previous note. 
*/
enum fluid_channel_legato_mode
{
	FLUID_CHANNEL_LEGATO_MODE_RETRIGGER, /**< Mode 0 - Release previous note, start a new note */
	FLUID_CHANNEL_LEGATO_MODE_MULTI_RETRIGGER, /**< Mode 1 - On contiguous notes retrigger in attack section using current value, shape attack using current dynamic and make use of previous voices if any */
	FLUID_CHANNEL_LEGATO_MODE_LAST /**< @internal Value defines the count of legato modes (#fluid_channel_legato_mode) @warning This symbol is not part of the public API and ABI stability guarantee and may change at any time! */
};

FLUIDSYNTH_API int fluid_synth_set_legato_mode(fluid_synth_t* synth, int chan, int legatomode);
FLUIDSYNTH_API int fluid_synth_get_legato_mode(fluid_synth_t* synth, int chan, int  *legatomode);

/* Interface to portamento mode  */
enum fluid_channel_portamento_mode
{
	FLUID_CHANNEL_PORTAMENTO_MODE_EACH_NOTE, /**< Mode 0 - Portamento on each note (staccato or legato) */
	FLUID_CHANNEL_PORTAMENTO_MODE_LEGATO_ONLY, /**< Mode 1 - Portamento only on legato note */
	FLUID_CHANNEL_PORTAMENTO_MODE_STACCATO_ONLY, /**< Mode 2 - Portamento only on staccato note */
	FLUID_CHANNEL_PORTAMENTO_MODE_LAST /**< @internal Value defines the count of portamento modes (#fluid_channel_portamento_mode) @warning This symbol is not part of the public API and ABI stability guarantee and may change at any time! */
};

FLUIDSYNTH_API int fluid_synth_set_portamento_mode(fluid_synth_t* synth,
						int chan, int portamentomode);
FLUIDSYNTH_API int fluid_synth_get_portamento_mode(fluid_synth_t* synth,
						int chan, int  * portamentomode);

/* Interface to breath mode   */
FLUIDSYNTH_API int fluid_synth_set_breath_mode(fluid_synth_t* synth, 
						int chan, int breathmode);
FLUIDSYNTH_API int fluid_synth_get_breath_mode(fluid_synth_t* synth,
						int chan, int  *breathmode);


#ifdef __cplusplus
}
#endif

#endif /* _FLUIDSYNTH_SYNTH_H */
