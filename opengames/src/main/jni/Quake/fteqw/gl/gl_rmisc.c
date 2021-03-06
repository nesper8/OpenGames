/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// r_misc.c

#include "quakedef.h"
#ifdef GLQUAKE
#include "glquake.h"
#include "gl_draw.h"

/*
==================
R_InitTextures
==================
*
void	GLR_InitTextures (void)
{
	int		x,y, m;
	qbyte	*dest;

// create a simple checkerboard texture for the default
	r_notexture_mip = Hunk_AllocName (sizeof(texture_t) + 16*16+8*8+4*4+2*2, "notexture");
	
	r_notexture_mip->width = r_notexture_mip->height = 16;
	r_notexture_mip->offsets[0] = sizeof(texture_t);
	r_notexture_mip->offsets[1] = r_notexture_mip->offsets[0] + 16*16;
	r_notexture_mip->offsets[2] = r_notexture_mip->offsets[1] + 8*8;
	r_notexture_mip->offsets[3] = r_notexture_mip->offsets[2] + 4*4;
	
	for (m=0 ; m<4 ; m++)
	{
		dest = (qbyte *)r_notexture_mip + r_notexture_mip->offsets[m];
		for (y=0 ; y< (16>>m) ; y++)
			for (x=0 ; x< (16>>m) ; x++)
			{
				if (  (y< (8>>m) ) ^ (x< (8>>m) ) )
					*dest++ = 0;
				else
					*dest++ = 0xff;
			}
	}	
}*/










#if 1
texid_t GenerateNormalisationCubeMap(void)
{
	texid_t normalisationCubeMap;
	unsigned char data[32*32*3];

	//some useful variables
	int size=32;
	float offset=0.5f;
	float halfSize=16.0f;
	vec3_t tempVector;
	unsigned char * bytePtr;

	int i, j;
	
	normalisationCubeMap = R_AllocNewTexture("normalisationcubemap", 32, 32, 0);
	GL_MTBind(0, GL_TEXTURE_CUBE_MAP_ARB, normalisationCubeMap);

	//positive x
	bytePtr=data;

	for(j=0; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			tempVector[0] = halfSize;			
			tempVector[1] = -(j+offset-halfSize);
			tempVector[2] = -(i+offset-halfSize);

			VectorNormalize(tempVector);

			bytePtr[0]=(unsigned char)((tempVector[0]/2 + 0.5)*255);
			bytePtr[1]=(unsigned char)((tempVector[1]/2 + 0.5)*255);
			bytePtr[2]=(unsigned char)((tempVector[2]/2 + 0.5)*255);

			bytePtr+=3;
		}
	}
	qglTexImage2D(	GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
					0, GL_RGBA, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//negative x
	bytePtr=data;

	for(j=0; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			tempVector[0] = (-halfSize);
			tempVector[1] = (-(j+offset-halfSize));
			tempVector[2] = ((i+offset-halfSize));

			VectorNormalize(tempVector);

			bytePtr[0]=(unsigned char)((tempVector[0]/2 + 0.5)*255);
			bytePtr[1]=(unsigned char)((tempVector[1]/2 + 0.5)*255);
			bytePtr[2]=(unsigned char)((tempVector[2]/2 + 0.5)*255);

			bytePtr+=3;
		}
	}
	qglTexImage2D(	GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
					0, GL_RGBA, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//positive y
	bytePtr=data;

	for(j=0; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			tempVector[0] = (i+offset-halfSize);
			tempVector[1] = (halfSize);
			tempVector[2] = ((j+offset-halfSize));

			VectorNormalize(tempVector);

			bytePtr[0]=(unsigned char)((tempVector[0]/2 + 0.5)*255);
			bytePtr[1]=(unsigned char)((tempVector[1]/2 + 0.5)*255);
			bytePtr[2]=(unsigned char)((tempVector[2]/2 + 0.5)*255);

			bytePtr+=3;
		}
	}
	qglTexImage2D(	GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
					0, GL_RGBA, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//negative y
	bytePtr=data;

	for(j=0; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			tempVector[0] = (i+offset-halfSize);
			tempVector[1] = (-halfSize);
			tempVector[2] = (-(j+offset-halfSize));

			VectorNormalize(tempVector);

			bytePtr[0]=(unsigned char)((tempVector[0]/2 + 0.5)*255);
			bytePtr[1]=(unsigned char)((tempVector[1]/2 + 0.5)*255);
			bytePtr[2]=(unsigned char)((tempVector[2]/2 + 0.5)*255);

			bytePtr+=3;
		}
	}
	qglTexImage2D(	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
					0, GL_RGBA, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//positive z
	bytePtr=data;

	for(j=0; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			tempVector[0] = (i+offset-halfSize);
			tempVector[1] = (-(j+offset-halfSize));
			tempVector[2] = (halfSize);

			VectorNormalize(tempVector);

			bytePtr[0]=(unsigned char)((tempVector[0]/2 + 0.5)*255);
			bytePtr[1]=(unsigned char)((tempVector[1]/2 + 0.5)*255);
			bytePtr[2]=(unsigned char)((tempVector[2]/2 + 0.5)*255);

			bytePtr+=3;
		}
	}
	qglTexImage2D(	GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
					0, GL_RGBA, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//negative z
	bytePtr=data;

	for(j=0; j<size; j++)
	{
		for(i=0; i<size; i++)
		{
			tempVector[0] = (-(i+offset-halfSize));
			tempVector[1] = (-(j+offset-halfSize));
			tempVector[2] = (-halfSize);

			VectorNormalize(tempVector);

			bytePtr[0]=(unsigned char)((tempVector[0]/2 + 0.5)*255);
			bytePtr[1]=(unsigned char)((tempVector[1]/2 + 0.5)*255);
			bytePtr[2]=(unsigned char)((tempVector[2]/2 + 0.5)*255);

			bytePtr+=3;
		}
	}
	qglTexImage2D(	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
					0, GL_RGBA, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	
		

	qglTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	qglTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	qglTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	qglTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	qglTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return normalisationCubeMap;
}


texid_t normalisationCubeMap;
#endif

/*
===============
R_Init
===============
*/
void GLR_ReInit (void)
{
	R_NetgraphInit();

	R_InitBloomTextures();
}
/*
typedef struct
{
   long offset;                 	// Position of the entry in WAD
   long dsize;                  	// Size of the entry in WAD file
   long size;                   	// Size of the entry in memory
   char type;                   	// type of entry
   char cmprs;                  	// Compression. 0 if none.
   short dummy;                 	// Not used
   char name[16];               	// we use only first 8
} wad2entry_t;
typedef struct
{
   char magic[4]; 			//should be WAD2
   long num;				//number of entries
   long offset;				//location of directory
} wad2_t;
void R_MakeTexWad_f(void)
{
	miptex_t dummymip = {"", 0, 0, {0, 0, 0, 0}};
	wad2_t wad2 = {"WAD2",0,0};
	wad2entry_t entry[2048];
	int entries = 0, i;
	FILE *f;
	char base[128];
	char *texname;
//	qbyte b;
	float scale;
	int width, height;

	qbyte *buf, *outmip;
	qbyte *mip, *stack;

//	WIN32_FIND_DATA fd;
//	HANDLE h;

	scale = atof(Cmd_Argv(2));
	if (!scale)
		scale = 2;

//	h = FindFirstFile(va("%s/textures/ *.tga", com_gamedir), &fd);	//if this is uncommented, clear that space... (gcc warning fix)
	if (!shader)
		return;
	mip = BZ_Malloc(1024*1024);
//	initbuf = BZ_Malloc(1024*1024*4);
	stack = BZ_Malloc(1024*1024*4+1024);
	f=fopen(va("%s/shadrtex.wad", com_gamedir), "wb");
	fwrite(&wad2, 1, sizeof(wad2_t), f);

	for (shad = shader; shad; shad=shad->next)
	{
		texname = shad->editorname;
		if (!*texname)
			continue;
		COM_StripExtension(shad->name, base);
		base[15]=0;
		for (i =0; i < entries; i++)
			if (!strcmp(entry[entries].name, base))
				break;
		if (i != entries)
		{
			Con_Printf("Skipped %s - duplicated shrunken name\n", texname);
			continue;
		}
		entry[entries].offset = ftell(f);
		entry[entries].dsize = entry[entries].size = 0;
		entry[entries].type = TYP_MIPTEX;
		entry[entries].cmprs = 0;
		entry[entries].dummy = 0;
		strcpy(entry[entries].name, base);

		strcpy(dummymip.name, base);

		{
	
			qbyte *data;
			int h;
			float x, xi;
			float y, yi;			

			char *path[] ={
		"%s",
		"override/%s.tga",
		"override/%s.pcx",
		"%s.tga",
		"progs/%s"};
			for (h = 0, buf=NULL; h < sizeof(path)/sizeof(char *); h++)
			{			
				buf = COM_LoadStackFile(va(path[h], texname), stack, 1024*1024*4+1024);
				if (buf)
					break;
			}
			if (!buf)
			{
				Con_Printf("Failed to find texture \"%s\"\n", texname);
				continue;
			}


data = ReadTargaFile(buf, com_filesize, &width, &height, false);
if (!data)
{
	BZ_Free(data);
	Con_Printf("Skipped %s - file type not supported (bad bpp?)\n", texname);
	continue;
}

			dummymip.width = (int)(width/scale) & ~0xf;
			dummymip.height = (int)(height/scale) & ~0xf;
			if (dummymip.width<=0)
				dummymip.width=16;
			if (dummymip.height<=0)
				dummymip.height=16;

			dummymip.offsets[0] = sizeof(dummymip);
			dummymip.offsets[1] = dummymip.offsets[0]+dummymip.width*dummymip.height;
			dummymip.offsets[2] = dummymip.offsets[1]+dummymip.width/2*dummymip.height/2;
			dummymip.offsets[3] = dummymip.offsets[2]+dummymip.width/4*dummymip.height/4;
			entry[entries].dsize = entry[entries].size = dummymip.offsets[3]+dummymip.width/8*dummymip.height/8;

			xi = (float)width/dummymip.width;
			yi = (float)height/dummymip.height;


			fwrite(&dummymip, 1, sizeof(dummymip), f);
			outmip=mip;
			for (outmip=mip, y = 0; y < height; y+=yi)
			for (x = 0; x < width; x+=xi)
			{
				*outmip++ = GetPaletteIndex(	data[(int)(x+y*width)*4+0],
								data[(int)(x+y*width)*4+1],
								data[(int)(x+y*width)*4+2]);
			}
			fwrite(mip, dummymip.width, dummymip.height, f);
			for (outmip=mip, y = 0; y < height; y+=yi*2)
			for (x = 0; x < width; x+=xi*2)
			{
				*outmip++ = GetPaletteIndex(	data[(int)(x+y*width)*4+0],
								data[(int)(x+y*width)*4+1],
								data[(int)(x+y*width)*4+2]);				
			}
			fwrite(mip, dummymip.width/2, dummymip.height/2, f);
			for (outmip=mip, y = 0; y < height; y+=yi*4)
			for (x = 0; x < width; x+=xi*4)
			{
				*outmip++ = GetPaletteIndex(	data[(int)(x+y*width)*4+0],
								data[(int)(x+y*width)*4+1],
								data[(int)(x+y*width)*4+2]);				
			}
			fwrite(mip, dummymip.width/4, dummymip.height/4, f);
			for (outmip=mip, y = 0; y < height; y+=yi*8)
			for (x = 0; x < width; x+=xi*8)
			{
				*outmip++ = GetPaletteIndex(	data[(int)(x+y*width)*4+0],
								data[(int)(x+y*width)*4+1],
								data[(int)(x+y*width)*4+2]);
			}
			fwrite(mip, dummymip.width/8, dummymip.height/8, f);

			BZ_Free(data);
		}
		entries++;
		Con_Printf("Added %s\n", base);
		GLSCR_UpdateScreen();
	}

	wad2.offset = ftell(f);
	wad2.num = entries;
	fwrite(entry, entries, sizeof(wad2entry_t), f);
	fseek(f, 0, SEEK_SET);
	fwrite(&wad2, 1, sizeof(wad2_t), f);
	fclose(f);


	BZ_Free(mip);
//	BZ_Free(initbuf);
	BZ_Free(stack);

	Con_Printf("Written %i mips to textures.wad\n", entries);
}
*/
void GLR_TimeRefresh_f (void);

extern cvar_t v_contrast, r_drawflat;
extern cvar_t r_stains, r_stainfadetime, r_stainfadeammount;

// callback defines
extern cvar_t gl_font;
extern cvar_t vid_conautoscale, vid_conheight, vid_conwidth;
extern cvar_t crosshair, crosshairimage, crosshaircolor, r_skyboxname;
extern cvar_t r_floorcolour, r_wallcolour, r_floortexture, r_walltexture;
extern cvar_t r_fastskycolour;
void GLV_Gamma_Callback(struct cvar_s *var, char *oldvalue);

void GLR_DeInit (void)
{
	Cmd_RemoveCommand ("timerefresh");

	Cmd_RemoveCommand ("makewad");

	Cvar_Unhook(&r_skyboxname);
	Cvar_Unhook(&vid_conautoscale);
	Cvar_Unhook(&vid_conheight);
	Cvar_Unhook(&vid_conwidth);
	Cvar_Unhook(&r_walltexture);
	Cvar_Unhook(&r_floortexture);
	Cvar_Unhook(&r_drawflat);
	Cvar_Unhook(&v_gamma);
	Cvar_Unhook(&v_contrast);

	Surf_DeInit();

	GLDraw_DeInit();
}

void GLR_Init (void)
{	
	Cmd_AddCommand ("timerefresh", GLR_TimeRefresh_f);

//	Cmd_AddCommand ("makewad", R_MakeTexWad_f);

//	Cvar_Hook(&r_floortexture, GLR_Floortexture_Callback);
//	Cvar_Hook(&r_walltexture, GLR_Walltexture_Callback);
//	Cvar_Hook(&r_drawflat, GLR_Drawflat_Callback);
	Cvar_Hook(&v_gamma, GLV_Gamma_Callback);
	Cvar_Hook(&v_contrast, GLV_Gamma_Callback);

	GLR_ReInit();
}

/*
===============
R_NewMap
===============
*/
void GLR_NewMap (void)
{
	char namebuf[MAX_QPATH];
	extern cvar_t host_mapname, r_shadow_realtime_dlight, r_shadow_realtime_world;
	int		i;
	
	for (i=0 ; i<256 ; i++)
		d_lightstylevalue[i] = 264;		// normal light value

	memset (&r_worldentity, 0, sizeof(r_worldentity));
	AngleVectors(r_worldentity.angles, r_worldentity.axis[0], r_worldentity.axis[1], r_worldentity.axis[2]);
	VectorInverse(r_worldentity.axis[1]);
	r_worldentity.model = cl.worldmodel;
	Vector4Set(r_worldentity.shaderRGBAf, 1, 1, 1, 1);
	VectorSet(r_worldentity.light_avg, 1, 1, 1);


	COM_StripExtension(COM_SkipPath(cl.worldmodel->name), namebuf, sizeof(namebuf));
	Cvar_Set(&host_mapname, namebuf);

	Surf_DeInit();

	r_viewleaf = NULL;
	r_viewcluster = -1;
	r_oldviewcluster = 0;
	r_viewcluster2 = -1;

	Mod_ParseInfoFromEntityLump(cl.worldmodel, cl.worldmodel->entities, cl.worldmodel->name);

TRACE(("dbg: GLR_NewMap: clear particles\n"));
	P_ClearParticles ();
TRACE(("dbg: GLR_NewMap: wiping them stains (getting the cloth out)\n"));
	Surf_WipeStains();
	CL_RegisterParticles();
TRACE(("dbg: GLR_NewMap: building lightmaps\n"));
	Surf_BuildLightmaps ();


TRACE(("dbg: GLR_NewMap: ui\n"));
#ifdef VM_UI
	UI_Reset();
#endif
TRACE(("dbg: GLR_NewMap: tp\n"));
	TP_NewMap();
	R_SetSky(cl.skyname);

#ifdef MAP_PROC
	if (cl.worldmodel->fromgame == fg_doom3)
		D3_GenerateAreas(cl.worldmodel);
#endif

#ifdef RTLIGHTS
	if (r_shadow_realtime_dlight.ival || r_shadow_realtime_world.ival)
	{
		R_LoadRTLights();
		if (rtlights_first == rtlights_max)
			R_ImportRTLights(cl.worldmodel->entities);
	}
	Sh_PreGenerateLights();
#endif
}

void GLR_PreNewMap(void)
{
	r_loadbumpmapping = r_deluxemapping.ival || r_shadow_realtime_world.ival || r_shadow_realtime_dlight.ival || r_glsl_offsetmapping.ival;
}


/*
====================
R_TimeRefresh_f

For program optimization
====================
*/
void GLR_TimeRefresh_f (void)
{
	int			i;
	float		start, stop, time;
	qboolean	finish;
	int			frames = 128;

	finish = atoi(Cmd_Argv(1));
	frames = atoi(Cmd_Argv(2));
	if (frames < 1)
		frames = 128;

#if defined(_WIN32) && !defined(_SDL)
	if (finish == 2)
	{
		extern HDC		maindc;
		qglFinish ();
		start = Sys_DoubleTime ();
		for (i=0 ; i<frames ; i++)
		{
			r_refdef.viewangles[1] = i/(float)frames*360.0;
			R_RenderView ();
			qSwapBuffers(maindc);
		}
	}
	else
#endif
	{
		if (qglDrawBuffer)
			qglDrawBuffer  (GL_FRONT);
		qglFinish ();

		start = Sys_DoubleTime ();
		for (i=0 ; i<frames ; i++)
		{
			r_refdef.viewangles[1] = i/(float)frames*360.0;
			R_RenderView ();
			if (finish)
				qglFinish ();
		}
	}
	qglFinish ();
	stop = Sys_DoubleTime ();
	time = stop-start;
	Con_Printf ("%f seconds (%f fps)\n", time, frames/time);

	if (qglDrawBuffer)
		qglDrawBuffer  (GL_BACK);
	GL_EndRendering ();
	GL_DoSwap();
}

#endif
