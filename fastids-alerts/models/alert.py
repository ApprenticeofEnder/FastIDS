from sqlmodel import Field, SQLModel

class Alert(SQLModel, table=True):
    id: int = Field(default=0, primary_key=True)
    message: str
    signature_id: int
    group_id: int
    classtype: str
    priority: int
    ip_source: str
    ip_dest: str
    port_source: int = Field(nullable=True)
    port_dest: int = Field(nullable=True)
    protocol: str
