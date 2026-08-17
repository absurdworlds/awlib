[library
	[shader name=default  vsh="shaders/v_tex.glsl" fsh="shaders/f_tex.glsl" ]
	[shader name=earth    vsh="shaders/earth.glsl" fsh="shaders/frag1.glsl" ]
	[shader name=texarray vsh="shaders/v_txa.glsl" fsh="shaders/f_txa.glsl" ]
	[shader name=v6       vsh="shaders/vert6.glsl" fsh="shaders/frag1.glsl" ]

	[texture
		name = butruck
		path = "materials/butruck.png"
	]
	[texture
		name = texarray
		paths = string:{
			"materials/m/des_dirt1.png",
			"materials/m/des_redrockbot.png",
			"materials/m/des_redrockmid.png",
			"materials/m/des_rocky1.png",
			"materials/m/des_rocky1_dirt1.png",
			"materials/m/des_oldrunway.png",
			"materials/m/des_oldrunwayblend.png",
			"materials/m/des_panelconc.png",
			"materials/m/des_dirttrack1r.png",
			"materials/m/des_dirttrackl.png",
			"materials/m/des_dirttrackx.png",
			"materials/m/des_dirttrack1.png",
			"materials/m/des_1line256.png",
			"materials/m/des_dirt2blend.png",
			"materials/m/vgs_shopwall01_128.png",
			"materials/m/vgs_shopwall01_128.png",
			"materials/m/des_scrub1_dirt1.png",
			"materials/m/des_scrub1.png",
			"materials/m/Tar_1line256HV.png",
			"materials/m/desstones_dirt1.png",
			"materials/m/parking2plain.png",
			"materials/m/Tar_lineslipway.png",
			"materials/m/parking2.png",
			"materials/m/rocktbrn_dirt2.png",
			"materials/m/rocktbrn128.png",
			"materials/m/des_roadedge1.png",
			"materials/m/des_ranchwall1.png",
			"materials/m/vgs_shopwall01_128.png",
			"materials/m/vgs_shopwall01_128.png",
			"materials/m/des_redrock2.png",
			"materials/m/des_redrock1.png" }
	]

	[material name=earth shader=earth ]
	[material name=default shader=default ]
	[material name=texarray shader=texarray texture=texarray ]
	[material name=v6 shader=v6 ]

	[model name=plane    path="models/plane6301.obj" ]
	[model name=butruck  path="models/butruck.obj" ]
	[model name=world    path="models/testworld.obj" ]
	[model name=patch    path="models/kusok2.obj" ]
	[model name=mattest  path="models/mattest.obj" ]
	[model name=cylinder path="models/cylinder.obj" ]
	[model name=box      path="models/box.obj" ]
]

[scene
	[object
		name=world
		model=world
		material=texarray
	]
	[object
		model=mattest
		material=texarray
		pos=float:{0, -5, 0}
	]
	[object
		model=patch
		material=v6
		pos=float:{4, 3, 20}
		rot=float:{0, 180, 0}
	]
	[object
		model=patch
		material=v6
		pos=float:{4, 3, 20}
		rot=float:{0, 180, 0}
	]
	[object
		model=cylinder
		material=v6
		pos=float:{0, 5, 20}
	]
	[object
		model=cylinder
		material=v6
		pos=float:{10, 5, 20}
		rot=float:{0, 45, 0}
	]
	[object
		model=cylinder
		material=v6
		pos=float:{-23, 4, -75}
	]
	[object
		model=cylinder
		material=v6
		pos=float:{-28, 4.2, -78}
	]
	[object
		model=cylinder
		material=v6
		pos=float:{-32, 4.35, -80}
	]
	[object
		model=box
		material=texarray
		pos=float:{0, 0, -10}
	]
	[object
		model=box
		material=v6
		pos=float:{0, 0, 0}
	]
	[object
		model=butruck
		material=default
		pos=float:{0, 3, 0}
	]
	[object
		model=butruck
		material=default
		pos=float:{0, 3, -10}
	]
	[object
		model=butruck
		material=default
		pos=float:{0, 3, -20}
	]
	[object
		model=butruck
		material=default
		pos=float:{300, 15.6, -2560}
		rot=float:{0, 57, 0}
	]
	[object
		model=butruck
		material=v6
		pos=float:{4, 3, 0}
	]
	[object
		model=cylinder
		material=v6
		pos=float:{4, 3, 0}
	]
]
