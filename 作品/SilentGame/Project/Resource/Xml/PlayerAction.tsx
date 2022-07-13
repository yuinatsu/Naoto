<?xml version="1.0" encoding="UTF-8"?>
<objectList name = "Player">
	<actionNode name="Move">
		<attach name="CheckKey" key="Non">
			<attach name="SetAnime" state = "Idle"/>
		</attach>
		<attach name="CheckKey" key="Up">
			<attach name ="ColisionCheck"speed="-5" height="-5">
				<attach name="SetAnime" state = "Up"/>
				<attach name="Move" y="-5"/>
			</attach>
		</attach>
		<attach name="CheckKey" key="Down">
			<attach name ="ColisionCheck"speed="5" height="5">
				<attach name="SetAnime" state = "Down"/>
				<attach name="Move" y="5"/>
			</attach>
		</attach>
		<attach name="CheckKey" key="Left">
			<attach name ="ColisionCheck"speed="-5" width="-5">
				<attach name="SetAnime" state = "Left"/>
				<attach name="Move" x="-5"/>
			</attach>
		</attach>
		<attach name="CheckKey" key="Right">
			<attach name ="ColisionCheck"speed="5" width="5">
				<attach name="SetAnime" state = "Right"/>
				<attach name="Move" x="5"/>
			</attach>
		</attach>
	</actionNode>
	<actionNode name="MoveSpeed">
		<attach name="CheckKey" key="Walk">
			<attach name="SpChange" speed="0.7"/>
		</attach>
		<attach name="CheckKey" key="Dash">
			<attach name="SetAnime" state = "Dash"/>
			<attach name="SpChange" speed="1.0"/>
		</attach>
		<attach name="CheckKey" key="Crouch">
			<attach name="SetAnime" state = "Crouch"/>
			<attach name="SpChange" speed="0.4"/>
		</attach>
	</actionNode>
	<actionNode name="Attack">
		<attach name="CheckKey" key="Attack">
			<attach name="SetAnime" state = "Attack"/>
			<attach name="Attack"/>
		</attach>
	</actionNode>
	<actionNode name="Item">
		<attach name="CheckKey" key="ItemLeft">
			<attach name="ItemCur" cur="Left"/>
		</attach>
		<attach name="CheckKey" key="ItemRight">
			<attach name="ItemCur" cur="Right"/>
		</attach>
	</actionNode>
</objectList>